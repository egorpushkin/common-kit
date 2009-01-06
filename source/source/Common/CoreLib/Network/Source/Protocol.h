#ifndef PROTOCOL_H__NETWORK__CORELIB__INCLUDED_
#define PROTOCOL_H__NETWORK__CORELIB__INCLUDED_

namespace Network
{

	class Protocol 
		: public mc::CommonImpl< IProtocol >
		, public mc::APImpl
		, public mc::AgentImpl
	{
	public:

		Protocol();

		// ICommon section
		DECLARE_INTERFACE_MAP()		

		// IProtocol section
		virtual mc::result AttachGateway(IClientRef gateway, ProtocolMode mode);

		virtual IClientPtr GetGateway();

		virtual void SetMode(ProtocolMode mode);

		virtual IMessagePtr Receive();

		virtual mc::result Send(IMessageRef message);

		virtual void SetMessagesMap(mc::IFactoryRef messagesMap);

		virtual mc::IFactoryPtr GetMessagesMap();

		virtual mc::result Spread(IMessageRef message);

		// IAgent section
		virtual mc::result Invoke(mc::DispId idMember, mc::DispParamsRef dispParams, mc::IVariantWrapperRef result, mc::RefIid iid);

	private:

		// Protocol private tools
		void ParseData();

		IMessagePtr MessageFromBuffer();

		// Event dispatchers	
		mc::result OnMessage(IMessageRef message);

	private:

		IClientPtr gateway_;

		unsigned long cookie_;

		ProtocolMode mode_;

		typedef enum tagState
		{

			ST_WAITING_HEADER = 0x01,
			
			ST_HEADER_PARSED

		}
		State;

		State state_;

		mc::IFactoryPtr messagesMap_;

		mc::IMutexPtr messagesLock_;

		typedef std::vector< Network::IMessagePtr > Messages_;

		Messages_ pendingMessages_;

		mc::ISemaphorePtr msgWaiter_;

		MessageImpl::MsgHeader_ msgHeader_;

		Components::IJobsQueuePtr msgJobs_;

	};

}

#endif // !PROTOCOL_H__NETWORK__CORELIB__INCLUDED_
