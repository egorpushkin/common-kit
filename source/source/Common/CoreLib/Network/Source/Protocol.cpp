#include "Common/Common.h"

#include "Protocol.h"

#include <limits>

#undef max

#include "MsgDeliveryJob.h"

namespace Network
{

	Protocol::Protocol()
		: mc::CommonImpl< IProtocol >()
		, mc::APImpl()
		, mc::AgentImpl()
		, gateway_()
		, cookie_()
		, mode_(PROTOCOL_SYNC)
		, state_(ST_WAITING_HEADER)
		, messagesMap_(mc::InstantiateFactory())
		, messagesLock_(mc::InstantiateMutex())
		, pendingMessages_()
		, msgWaiter_(mc::InstantiateSemaphore())
		, msgHeader_()
		, msgJobs_()
	{
	}

	// ICommon section
	BEGIN_INTERFACE_MAP(Protocol)
		COMMON(IProtocol)
		INTERFACE(IProtocol)
		IMPL(mc::APImpl)
		IMPL(mc::AgentImpl)
		IMPL(mc::ItemImpl)
	END_INTERFACE_MAP()		

	// IProtocol section
	mc::result Protocol::AttachGateway(IClientRef gateway, ProtocolMode mode)
	{
		if ( gateway_ || !gateway )
			return mc::_E_FAIL;

		// Init engine
		pendingMessages_.clear();
		msgWaiter_->Init(0, std::numeric_limits< long >::max());
		state_ = ST_WAITING_HEADER;

		gateway_ = gateway;
		SetMode(mode);

		// Attach to gateway 'on data' notifications 		
		mc::Advise(mc::ICommonPtr(gateway_, mc::IID_ICommon), mc::ItemImpl::GetLocal(), cookie_);

		// Start reading data
		gateway_->AsyncRead();				

		return mc::_S_OK;
	}

	IClientPtr Protocol::GetGateway()
	{
		return gateway_;
	}

	void Protocol::SetMode(ProtocolMode mode)
	{
		mc::MutexLock lock(messagesLock_);

		if ( mode == mode_ )
			return;

		if ( PROTOCOL_ASYNC == mode )
		{
			msgJobs_ = Components::InstantiateJobsQueue();
			msgJobs_->Start();

			// All pending messages must be asynchronously processed
			while ( pendingMessages_.size() > 0 )
				OnMessage(Receive());				
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
		if ( mc::IsFailed(msgWaiter_->AcquireSem()) )
			return NULL;

		mc::MutexLock lock(messagesLock_);

		IMessagePtr msg = pendingMessages_.front();
		pendingMessages_.erase(pendingMessages_.begin());

		return msg;
	}

	mc::result Protocol::Send(IMessageRef message)
	{
		if ( !message || !gateway_ )
			return mc::_E_FAIL;

		return message->Write(gateway_);
	}

	void Protocol::SetMessagesMap(mc::IFactoryRef messagesMap)
	{
		messagesMap_ = messagesMap;
	}

	mc::IFactoryPtr Protocol::GetMessagesMap()
	{
		return messagesMap_;
	}

	mc::result Protocol::Spread(IMessageRef message)
	{
		if ( !message || !gateway_ )
			return mc::_E_FAIL;

		return mc::APImpl::SpreadBase(
			AGENTID_MESSAGE, 
			mc::CreateParams(
				mc::ItemImpl::GetLocal(), // Param 1: Protocol
				gateway_, // Param 2: Client
				message // Param 3: message
			));
	}

	// IAgent section
	mc::result Protocol::Invoke(mc::DispId idMember, mc::DispParamsRef /* dispParams */, mc::IVariantWrapperRef /* result */, mc::RefIid /* iid */)
	{
		if ( Network::AGENTID_DATA == idMember )
		{
			ParseData();

			// Continue reading data
			if ( gateway_ )
				gateway_->AsyncRead();	
		}

		return mc::_S_OK;
	}

	// Protocol private tools
	void Protocol::ParseData()
	{
		mc::MutexLock lock(messagesLock_);

		IMessagePtr message;
		while ( message = MessageFromBuffer() )
		{
			if ( PROTOCOL_SYNC == mode_ )
			{
				pendingMessages_.push_back(message);

				msgWaiter_->ReleaseSem();
			}
			else if ( PROTOCOL_ASYNC == mode_ )
			{
				OnMessage(message);
			}
		}
	}

	IMessagePtr Protocol::MessageFromBuffer()
	{
		if ( !gateway_ )
			return NULL;	

		asio::streambuf& buffer = gateway_->GetBuffer();

		if ( ST_WAITING_HEADER == state_ )
		{
			if ( buffer.size() < MessageImpl::GetHeaderSize() )
				return NULL;

			// Read message header
			if ( !msgHeader_.Read(buffer) )
			{
				// Clear buffer
				buffer.consume(buffer.size());				
				return NULL;
			}

			state_ = ST_HEADER_PARSED;

			return MessageFromBuffer();
		}
		else if ( ST_HEADER_PARSED == state_ )
		{
			if ( !MessageImpl::IsMsgBodyReady(buffer.size(), msgHeader_) )
				return NULL;

			state_ = ST_WAITING_HEADER;

			// Construct message from msgHeader_.code_ and serialize it from stream
			IMessagePtr msg(messagesMap_->Create(msgHeader_.GetCode()), IID_IMessage);
			if ( !msg )
			{
				// Remove message from buffer
				buffer.consume(msgHeader_.GetSize() - MessageImpl::GetHeaderSize());		
				return NULL;
			}

			if ( mc::IsFailed(msg->Read(buffer)) )
				return NULL;

			return msg;
		}

		return NULL;
	}

	// Event dispatchers	
	mc::result Protocol::OnMessage(IMessageRef message)
	{
		if ( !msgJobs_ )
			return mc::_E_FAIL;

		// Schedule new message delivery job
		msgJobs_->Push(
			mc::InstantiateAgent< MsgDeliveryJob >(),
			mc::CreateParams(
				mc::ItemImpl::GetLocal(), // Param 1: Network::Protocol
				message // Param 2: New message
			)
		);

		return mc::_S_OK;
	}

	// External tools
	IProtocolPtr InstantiateProtocol()
	{
		return IProtocolPtr(mc::ObjectCreator< Protocol >(), IID_IProtocol);
	}

}
