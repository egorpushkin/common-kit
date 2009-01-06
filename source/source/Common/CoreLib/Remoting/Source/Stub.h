#ifndef STUB_H__REMOTING__CORELIB__INCLUDED_
#define STUB_H__REMOTING__CORELIB__INCLUDED_

namespace Remoting
{

	class Stub
		: public mc::CommonImpl< IStub >
		, public mc::AgentImpl
		, public mc::ItemImpl
	{
	public:

		Stub();

		// ICommon section
		DECLARE_INTERFACE_MAP()		

		// IStub section
		virtual mc::result Initialize(Network::IProtocolRef protocol, Network::IClient::Id_ clientId, mc::RefClsid objId);

		virtual mc::result Initialize(Network::IProtocolRef protocol, Network::IClient::Id_ clientId, mc::ICommonRef target, Behaviour mode, Network::IHostRef host);

		Network::IClient::Id_ GetClientId();

		// IAgent section
		virtual mc::result Invoke(mc::DispId idMember, mc::DispParamsRef dispParams, mc::IVariantWrapperRef result, mc::RefIid iid);

	private:

		// Requests
		mc::ICommonPtr InstantiateFromId(mc::RefClsid objId);

		// Tools
		mc::IAgentPtr PrepareCallTarget(mc::RefIid iid);

	private:

		mc::IMutexPtr lock_;

		Behaviour mode_;

		ITransmitterPtr transmitter_;

		Network::IProtocolPtr protocol_;

		Network::IClient::Id_ clientId_;

		mc::ICommonPtr targetCommon_;

		Network::IHostPtr host_;

	};

}

#endif // !STUB_H__REMOTING__CORELIB__INCLUDED_
