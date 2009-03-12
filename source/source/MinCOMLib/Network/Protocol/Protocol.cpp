#include "Common/Common.h"

#include "Protocol.h"

// Required for std::numeric_limits< T >::max() to work.
#undef max 

namespace MinCOM
{

	Protocol::Protocol(IConnectionRef connection, IProtocol::Mode_ mode)
		: CommonImpl< IProtocol >()
		, APImpl()
		, connection_( connection )
		, cookie_()
		, mode_( mode )
		, state_( ST_WAITING_HEADER )
		, messagesMap_( Library::Factory() )
		, pendingMessages_()
		, msgWaiter_()
		, msgHeader_()
		, protocolEvents_()
	{
		Init();
	}

	Protocol::~Protocol()
	{
		Cleanup();
	}

	// IProtocol section
	IConnectionPtr Protocol::GetConnection()
	{
		return connection_;
	}

	void Protocol::SetMode(Mode_ mode)
	{
        // TODO: Find the origin of this error.
		CoreMutexLock locker( CommonImpl< IProtocol >::GetLock() );

		// Check whether mode should be changed.
		if ( mode == mode_ )
			return;

		// Save new mode.
		mode_ = mode;

		// Apply made changes.
		ApplyMode();
	}

	IProtocol::Mode_ Protocol::GetMode()
	{
		return mode_;
	}

	IMessagePtr Protocol::Receive()
	{
		// Should check whether waiter is alive and wait until a message arrives.
		if ( msgWaiter_ && Error::IsFailed(msgWaiter_->Wait()) )
			return NULL;

		// Must lock only nonblocking part of the method to prevent inability to 
		// access the object while it is waiting. 'Receive' call should not 
		// prevent from changing protocol operating mode.
		CoreMutexLock locker( CommonImpl< IProtocol >::GetLock() );

		// Extract message from the queue and return it.
		IMessagePtr msg = pendingMessages_.front();
		pendingMessages_.pop();

		return msg;
	}

	result Protocol::Send(IMessageRef message)
	{
		MC_LOG_ROUTINE;

        // Validate current object's state and input arguments.
		if ( !message || !connection_ )
			return _E_FAIL;
        // Serialize message to stream.
		std::ostream stream( &connection_->GetOStreamBuf() );
		message->Write(stream);
        // Send the entire content of input stream. 
		MC_LOG_STATEMENT("Attempting to write data to the connection.");
		connection_->Write();
        return _S_OK;
	}

	void Protocol::SetMessagesMap(IFactoryRef messagesMap)
	{
		CoreMutexLock locker( CommonImpl< IProtocol >::GetLock() );
		messagesMap_ = messagesMap;
	}

	IFactoryPtr Protocol::GetMessagesMap()
	{
		return messagesMap_;
	}

	// DRawData section
	result Protocol::Connected(IConnectionRef /* connection */)
	{
		return _E_NOTIMPL;
	}

	result Protocol::DataReceived(IConnectionRef /* connection */)
	{
		// This method should be locked because this notification is generally
		// comes from another thread.
		CoreMutexLock locker( CommonImpl< IProtocol >::GetLock() );

		// Parse arrived data.
		ParseData();
		// Initiate next data receiving loop.
		if ( connection_ )
			connection_->ReadAsync();	
		return _S_OK;
	}

	result Protocol::Disconnected(IConnectionRef /* connection */)
	{
		// Notify clients on the fact that connection is lost.
		protocolEvents_->Disconnected(CommonImpl< IProtocol >::GetSelf());
		// Protocol object cannot continue functioning in normal way. 
		// Therefore, cleanup is required.
		Cleanup();

		return _S_OK;
	}

	// ICommon section
	result Protocol::PostInit()
	{
		// Register self events
		protocolEvents_ = APImpl::AdviseAndThrow( TypeInfo< DProtocol >::GetGuid() );

		// Subscribe on events from attached connection and ...
		Events::Advise(connection_, CommonImpl< IProtocol >::GetSelf(), cookie_, TypeInfo< DRawData >::GetGuid());
		// ... start receiving data immediately.
		connection_->ReadAsync();	

		return _S_OK;
	}

	// Protocol internal tools
	void Protocol::Init()
	{
		// Check whether connection is configured correctly.
		if ( !connection_ )
			throw std::exception();

		// Configure protocol mode.
		ApplyMode();
	}

	void Protocol::ApplyMode()
	{
		if ( ASYNC == mode_ )
		{
			// Destroy waiter semaphore. This causes for 'Receive' method to 
			// return NULL immediately.
			msgWaiter_ = NULL;

			// All pending messages must be asynchronously processed.
			while ( pendingMessages_.size() > 0 )
			{
				// Extract next message ... 
				IMessagePtr msg = pendingMessages_.front();
				pendingMessages_.pop();
				// ... and notify subscribers.
				protocolEvents_->MessageArrived(CommonImpl< IProtocol >::GetSelf(), msg);				
			}
		}
		else if ( SYNC == mode_ )
		{
			// Create waiter object.
			msgWaiter_ = Library::Semaphore(0, std::numeric_limits< long >::max());
		}
	}

	void Protocol::ParseData()
	{
		CoreMutexLock locker( CommonImpl< IProtocol >::GetLock() );

		IMessagePtr message;
		while ( message = MessageFromBuffer() )
		{
			if ( SYNC == mode_ )
			{
				// Register message.
				pendingMessages_.push(message);
				// Request message delivery.
				msgWaiter_->Release();
			}
			else if ( ASYNC == mode_ )
			{
				// Deliver message synchronously.
				protocolEvents_->MessageArrived(CommonImpl< IProtocol >::GetSelf(), message);
			}
		}
	}

	IMessagePtr Protocol::MessageFromBuffer()
	{
		if ( !connection_ )
			return NULL;	

		std::istream stream(&connection_->GetIStreamBuf());

		if ( ST_WAITING_HEADER == state_ )
		{
			if ( connection_->GetISize() < MessageImpl::GetHeaderSize() )
				// This is not an error. This indicates that not enough data is
				// received.
				return NULL;

			// Read message header
			if ( !msgHeader_.Read(stream) )
			{
				// Error has occurred. See MessageImpl::MsgHeader_ to determine
				// what situation is treated as error.
				protocolEvents_->DataErrorOccured(CommonImpl< IProtocol >::GetSelf());
				// Protocol object cannot continue functioning in normal way. 
				// Therefore, cleanup is required.
				Cleanup();
				return NULL;
			}

			state_ = ST_HEADER_PARSED;

			return MessageFromBuffer();
		}
		else if ( ST_HEADER_PARSED == state_ )
		{
			if ( !MessageImpl::IsMsgBodyReady(connection_->GetISize(), msgHeader_) )
				// This is not an error. This indicates that not enough data is
				// received.
				return NULL;

			state_ = ST_WAITING_HEADER;

			// Construct message from msgHeader_.code_ and serialize it from 
			// stream.
			IMessagePtr msg(messagesMap_->Create(msgHeader_.GetCode()));
			if ( !msg )
			{
				// Message was received and extracted from buffer, but! it
				// was not serialized from stream correctly because 
				// corresponding (by code) record was not found in the registry.
				// Protocol may continue functioning without delivery of any
				// notifications or cleanup.

				// TODO: Actually message was received but not extracted. It should
				// be done here.
				return NULL;
			}

			// Set code forcibly. This should be done to allow use of 
			// MessageImpl directly without deriving additional classes for
			// simple command messages without arguments.
			msg->SetCode(msgHeader_.GetCode());
			
			// Attempt to read message body.
			if ( Error::IsFailed(msg->Read(stream)) )
			{
				// Message was not correctly serialized from stream. 
				// Spread corresponding error.
				protocolEvents_->DataErrorOccured(CommonImpl< IProtocol >::GetSelf());
				// Protocol object cannot continue functioning in normal way. 
				// Therefore, cleanup is required.
				Cleanup();
				return NULL;
			}

			return msg;
		} 

		return NULL;
	}

	void Protocol::Cleanup()
	{
		// Must unsubscribe itself from connection events.
		if ( connection_ )
		{
			Events::Unadvise(connection_, cookie_, TypeInfo< DRawData >::GetGuid());
		}
		// Must release local resources.
		msgWaiter_ = NULL;
		connection_ = NULL;
		while ( pendingMessages_.size() > 0 )
			pendingMessages_.pop();
	}

}
