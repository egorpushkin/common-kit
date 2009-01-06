#ifndef IPROXY_H__REMOTING__COMMONKIT__INCLUDED_
#define IPROXY_H__REMOTING__COMMONKIT__INCLUDED_

namespace Remoting
{

	interface IProxy : public mc::ICommon
	{
	
		virtual mc::result Instantiate(mc::RefClsid clsid, Network::IHostRef host) = 0;

		virtual mc::result Instantiate(Network::IProtocolRef protocol, Network::IClient::Id_ clientId, IServerRef server, Behaviour mode, Network::IHostRef host) = 0;

	};

	typedef mc::ComPtr< IProxy > IProxyPtr;
	typedef const IProxyPtr& IProxyRef;

	// {0cc2d875-4a0b-49ba-a9ca-6713ce18b61b} 
	MC_DEFINE_GUID(IID_IProxy, 
	0x0cc2d875, 0x4a0b, 0x49ba, 0xa9, 0xca, 0x67, 0x13, 0xce, 0x18, 0xb6, 0x1b);

	// {9C3C9D4C-818C-41ef-AA94-E4E3AD2CEEE7}
	MC_DEFINE_GUID(CLSID_Proxy, 
	0x9c3c9d4c, 0x818c, 0x41ef, 0xaa, 0x94, 0xe4, 0xe3, 0xad, 0x2c, 0xee, 0xe7);

}

#endif // !IPROXY_H__REMOTING__COMMONKIT__INCLUDED_
