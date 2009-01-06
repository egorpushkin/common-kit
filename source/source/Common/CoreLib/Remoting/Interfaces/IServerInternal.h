#ifndef ISERVERINTERNAL_H__REMOTING__COMMONKIT__INCLUDED_
#define ISERVERINTERNAL_H__REMOTING__COMMONKIT__INCLUDED_

namespace Remoting
{

	interface IServerInternal : public mc::ICommon
	{

		virtual mc::result RunPassive() = 0;

		virtual mc::result RegisterStub(IStubRef stub) = 0;

		virtual mc::result AttachObject(void* id, Network::IClient::Id_ clientId, mc::ICommonRef object) = 0;

		virtual mc::ICommonPtr RemitProxy(void* id, Network::IClient::Id_ clientId) = 0;

		virtual Network::IClient::Id_ GenerateUniqueClientId() = 0;

	};

	typedef mc::ComPtr< IServerInternal > IServerInternalPtr;
	typedef const IServerInternalPtr& IServerInternalRef;

	// {3e07bcbb-44f3-4bee-98b2-26a7a7402f59} 
	MC_DEFINE_GUID(IID_IServerInternal, 
	0x3e07bcbb, 0x44f3, 0x4bee, 0x98, 0xb2, 0x26, 0xa7, 0xa7, 0x40, 0x2f, 0x59);

	typedef enum tagProtocolEvents
	{

		AGENTID_STOPSERVICE = 0xff010f01

	}
	ProtocolEvents;

}

#endif // !ISERVERINTERNAL_H__REMOTING__COMMONKIT__INCLUDED_
