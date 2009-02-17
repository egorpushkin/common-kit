#ifndef PROTOCOL_H__MINCOMLIB__INCLUDED_
#define PROTOCOL_H__MINCOMLIB__INCLUDED_

namespace MinCOM
{

	class Protocol 
		: public CommonImpl< IProtocol >
		, public CommonImpl< DRawData >
		, APImpl
	{
        using CommonImpl< IProtocol >::__Cast;
        
	public:
        
		Protocol();
		virtual ~Protocol();

		// IProtocol section
		virtual result AttachConnection(IConnectionRef connection, ProtocolMode mode = PROTOCOL_SYNC);
		
		virtual IConnectionPtr GetConnection();

		virtual void SetMode(ProtocolMode mode);
		
		virtual IMessagePtr Receive();
		
		virtual result Send(IMessageRef message);
		
		virtual void SetMessagesMap(IFactoryRef messagesMap);
		
		virtual IFactoryPtr GetMessagesMap();

		// DRawData section
		virtual result Connected(IConnectionRef connection);
		
		virtual result DataReceived(IConnectionRef connection);
		
		virtual result Disconnected(IConnectionRef connection);

		// ICommon section
		virtual result PostInit();

	private:

		void ParseData();

		IMessagePtr MessageFromBuffer();

	private:

		IConnectionPtr connection_;

		unsigned long cookie_;

		ProtocolMode mode_;

		typedef enum tagState
		{

			ST_WAITING_HEADER = 0x01,
			
			ST_HEADER_PARSED

		}
		State;

		State state_;

		IFactoryPtr messagesMap_;

		typedef std::vector< IMessagePtr > Messages_;

		Messages_ pendingMessages_;

		ISemaphorePtr msgWaiter_;

		MessageImpl::MsgHeader_ msgHeader_;

		IJobsQueuePtr msgJobs_;

		DProtocolPtr protocolEvents_;

	};

}

#endif // !PROTOCOL_H__MINCOMLIB__INCLUDED_
