#ifndef ISTUB_H__REMOTING__COMMONKIT__INCLUDED_
#define ISTUB_H__REMOTING__COMMONKIT__INCLUDED_

namespace Remoting
{

	interface IStub : public mc::ICommon
	{

		virtual mc::result Initialize(Network::IProtocolRef protocol, Network::IClient::Id_ clientId, mc::RefClsid objId) = 0;

		virtual mc::result Initialize(Network::IProtocolRef protocol, Network::IClient::Id_ clientId, mc::ICommonRef target, Behaviour mode, Network::IHostRef host) = 0;

		virtual Network::IClient::Id_ GetClientId() = 0;

	};

	typedef mc::ComPtr< IStub > IStubPtr;
	typedef const IStubPtr& IStubRef;

	// {104bc6fc-e53d-4a3c-a8f7-4edded033d36} 
	MC_DEFINE_GUID(IID_IStub, 
	0x104bc6fc, 0xe53d, 0x4a3c, 0xa8, 0xf7, 0x4e, 0xdd, 0xed, 0x03, 0x3d, 0x36);

}

#endif // !ISTUB_H__REMOTING__COMMONKIT__INCLUDED_

