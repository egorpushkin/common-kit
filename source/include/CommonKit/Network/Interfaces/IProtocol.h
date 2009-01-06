#ifndef IPROTOCOL_H__NETWORK__COMMONKIT__INCLUDED_
#define IPROTOCOL_H__NETWORK__COMMONKIT__INCLUDED_

namespace Network
{

	typedef enum tagProtocolMode 
	{		

		PROTOCOL_SYNC = 0x0,

		PROTOCOL_ASYNC

	} 
	ProtocolMode;

	interface IProtocol : public mc::ICommon
	{

		virtual mc::result AttachGateway(IClientRef gateway, ProtocolMode mode = PROTOCOL_SYNC) = 0;

		virtual IClientPtr GetGateway() = 0;

		virtual void SetMode(ProtocolMode mode) = 0;

		virtual IMessagePtr Receive() = 0;

		virtual mc::result Send(IMessageRef message) = 0;

		virtual void SetMessagesMap(mc::IFactoryRef messagesMap) = 0;

		virtual mc::IFactoryPtr GetMessagesMap() = 0;

		virtual mc::result Spread(IMessageRef message) = 0;
		
	};

	typedef mc::ComPtr< IProtocol > IProtocolPtr;
	typedef const IProtocolPtr& IProtocolRef;

	// {fd3fec5e-51b4-4dd3-913e-1b59de3d0fb4} 
	MC_DEFINE_GUID(IID_IProtocol, 
	0xfd3fec5e, 0x51b4, 0x4dd3, 0x91, 0x3e, 0x1b, 0x59, 0xde, 0x3d, 0x0f, 0xb4);

	typedef enum tagProtocolEvents
	{

		AGENTID_MESSAGE = 0xff010E02

	}
	ProtocolEvents;

	IProtocolPtr InstantiateProtocol();

}

#endif // !IPROTOCOL_H__NETWORK__COMMONKIT__INCLUDED_
