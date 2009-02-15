#include "Common/Common.h"

#include "Protocol.h"

// Required for std::numeric_limits< T >::max() to work.
#undef max 

namespace MinCOM
{

	Protocol::Protocol()
		: CommonImpl< IProtocol >()
		, APImpl()
		, connection_()
		, cookie_()
		, mode_( PROTOCOL_SYNC )
		, state_( ST_WAITING_HEADER )
		, messagesMap_( Library::Factory() )
		, pendingMessages_()
		, msgWaiter_( Library::Semaphore(0, std::numeric_limits< long >::max()) )
		, msgHeader_()
		, msgJobs_()
		, protocolEvents_()
	{
	}

	Protocol::~Protocol()
	{
		// TODO: Must unsubscribe from connection events.
	}

	// IProtocol section
	mc::result Protocol::AttachConnection(IConnectionRef connection, ProtocolMode mode /* = PROTOCOL_SYNC */)
	{
		CoreMutexLock locker( CommonImpl< IProtocol >::GetLock() );

		if ( connection_ || !connection )
			return mc::_E_FAIL;

		// Init engine
		pendingMessages_.clear();
		state_ = ST_WAITING_HEADER;

		// Save input data
		connection_ = connection;
		SetMode(mode);

		// Attach to gateway 'on data' notifications 		
		Events::Advise(connection_, CommonImpl< IProtocol >::GetSelf(), cookie_, TypeInfo< DRawData >::GetGuid());

		// Start reading data
		connection_->ReadAsync();				

		return mc::_S_OK;
	}

	IConnectionPtr Protocol::GetConnection()
	{
		return connection_;
	}

	void Protocol::SetMode(ProtocolMode mode)
	{
		CoreMutexLock locker( CommonImpl< IProtocol >::GetLock() );

		if ( mode == mode_ )
			return;

		if ( PROTOCOL_ASYNC == mode )
		{
			msgJobs_ = Library::JobsQueue();
			msgJobs_->Run();

			// All pending messages must be asynchronously processed
			while ( pendingMessages_.size() > 0 )
				protocolEvents_->MessageArrived(Receive());				
		}
		else if ( PROTOCOL_SYNC == mode )
		{
			if ( msgJobs_ )
				msgJobs_->Stop();
			msgJobs_ = NULL;
		}

		mode_ = mode;
	}

	IMessagePtr Protocol::Receive()
	{
		if ( Error::IsFailed(msgWaiter_->Wait()) )
			return NULL;

		CoreMutexLock locker( CommonImpl< IProtocol >::GetLock() );

		IMessagePtr msg = pendingMessages_.front();
		pendingMessages_.erase(pendingMessages_.begin());

		return msg;
	}

	result Protocol::Send(IMessageRef message)
	{
		if ( !message || !connection_ )
			return _E_FAIL;

		std::ostream stream( &connection_->GetOStreamBuf() );
		return message->Write(stream);
	}

	void Protocol::SetMessagesMap(IFactoryRef messagesMap)
	{
		messagesMap_ = messagesMap;
	}

	IFactoryPtr Protocol::GetMessagesMap()
	{
		return messagesMap_;
	}

	// DRawData section
	result Protocol::Connected(IConnectionRef connection)
	{
		return _E_NOTIMPL;
	}

	result Protocol::DataReceived(IConnectionRef connection)
	{
		// Parse arrived data.
		ParseData();
		// Initiate next data receiving loop.
		if ( connection_ )
			connection_->ReadAsync();	
		return _S_OK;
	}

	result Protocol::Disconnected(IConnectionRef connection)
	{
		return _E_NOTIMPL;
	}

	// ICommon section
	result Protocol::PostInit()
	{
		protocolEvents_ = APImpl::AdviseAndThrow( TypeInfo< DProtocol >::GetGuid() );
		return _S_OK;
	}

	// Protocol internal tools
	void Protocol::ParseData()
	{
		CoreMutexLock locker( CommonImpl< IProtocol >::GetLock() );

		IMessagePtr message;
		while ( message = MessageFromBuffer() )
		{
			if ( PROTOCOL_SYNC == mode_ )
			{
				// Register message.
				pendingMessages_.push_back(message);
				// Request message delivery.
				msgWaiter_->Release();
			}
			else if ( PROTOCOL_ASYNC == mode_ )
			{
				// Deliver message synchronously.
				protocolEvents_->MessageArrived(message);
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
				return NULL;

			// Read message header
			if ( !msgHeader_.Read(stream) )
			{
				// Clear buffer
				// buffer.consume(buffer.size());				
				return NULL;
			}

			state_ = ST_HEADER_PARSED;

			return MessageFromBuffer();
		}
		else if ( ST_HEADER_PARSED == state_ )
		{
			if ( !MessageImpl::IsMsgBodyReady(connection_->GetISize(), msgHeader_) )
				return NULL;

			state_ = ST_WAITING_HEADER;

			// Construct message from msgHeader_.code_ and serialize it from stream.
			IMessagePtr msg(messagesMap_->Create(msgHeader_.GetCode()));
			if ( !msg )
			{
				// Remove message from buffer
				// buffer.consume(msgHeader_.GetSize() - MessageImpl::GetHeaderSize());		
				return NULL;
			}

			if ( Error::IsFailed(msg->Read(stream)) )
				return NULL;

			return msg;
		} 

		return NULL;
	}

}
