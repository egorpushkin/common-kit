#ifndef PROXY_H__REMOTING__CORELIB__INCLUDED_
#define PROXY_H__REMOTING__CORELIB__INCLUDED_

namespace Remoting
{

	class Proxy
		: public mc::CommonImpl< IProxy >
		, public mc::AgentImpl
		, public mc::ItemImpl
	{
	public:

		Proxy();

		// ICommon section
		DECLARE_INTERFACE_MAP()		

		// IProxy section
		virtual mc::result Instantiate(mc::RefClsid clsid, Network::IHostRef host);

		virtual mc::result Instantiate(Network::IProtocolRef protocol, Network::IClient::Id_ clientId, IServerRef server, Behaviour mode, Network::IHostRef host);

		// IAgent section
		virtual mc::result Invoke(mc::DispId idMember, mc::DispParamsRef dispParams, mc::IVariantWrapperRef result, mc::RefIid iid);

	private:

		mc::IMutexPtr lock_;

		Behaviour mode_;

		ITransmitterPtr transmitter_;

		Network::IProtocolPtr protocol_;

		Network::IHostPtr host_;

		IServerPtr server_;

		Network::IClient::Id_ clientId_;

	};

}

#endif // !PROXY_H__REMOTING__CORELIB__INCLUDED_
