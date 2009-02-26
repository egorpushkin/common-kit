#ifndef PROTOCOL_H__MINCOMLIB__INCLUDED_
#define PROTOCOL_H__MINCOMLIB__INCLUDED_

namespace MinCOM
{

	class Protocol 
		: public CommonImpl< IProtocol >
		, public CommonImpl< DRawData >
		, public APImpl
	{
	public:

		typedef CommonImpl< IProtocol > ClassRoot_;  
        
		Protocol(IConnectionRef connection, IProtocol::Mode_ mode);

		virtual ~Protocol();

		// IProtocol section
		virtual IConnectionPtr GetConnection();

		virtual void SetMode(Mode_ mode);

		virtual Mode_ GetMode();
		
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

		void Init();

		void ApplyMode();

		void ParseData();

		IMessagePtr MessageFromBuffer();

		void Cleanup();

	private:

		IConnectionPtr connection_;

		unsigned long cookie_;

		Mode_ mode_;

		typedef enum tagState
		{

			ST_WAITING_HEADER = 0x01,
			
			ST_HEADER_PARSED

		}
		State;

		State state_;

		IFactoryPtr messagesMap_;

		std::queue< IMessagePtr > pendingMessages_;

		ISemaphorePtr msgWaiter_;

		MessageImpl::MsgHeader_ msgHeader_;

		DProtocolPtr protocolEvents_;

	};

}

#endif // !PROTOCOL_H__MINCOMLIB__INCLUDED_
