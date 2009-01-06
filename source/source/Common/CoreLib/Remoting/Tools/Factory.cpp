#include "Common/Common.h"

#include "Remoting/Interfaces/Common.h"

#include "Remoting/Interfaces/ITransmitter.h"

#include "Remoting/Interfaces/IProxy.h"

#include "Remoting/Source/Proxy.h"

namespace Remoting
{

	namespace Private
	{

		IProxyPtr InstantiateProxy()
		{
			// Construct and configure proxy
			mc::ICommonPtr proxyCommon(mc::ObjectCreator< Proxy >());
			if ( !proxyCommon )
				return NULL;

			return IProxyPtr(proxyCommon, IID_IProxy);
		}

	}

	mc::ICommonPtr Instantiate(mc::RefClsid clsid, Network::IHostRef host)
	{
		IProxyPtr proxy = Private::InstantiateProxy();
		if ( !proxy )
			return NULL;

		if ( mc::IsFailed(proxy->Instantiate(clsid, host)) )
			return NULL;

		return mc::ICommonPtr(proxy, mc::IID_ICommon);
	}

	mc::ICommonPtr InstantiateProxy(Network::IProtocolRef protocol, Network::IClient::Id_ clientId, IServerRef server, Behaviour mode, Network::IHostRef host)
	{
		IProxyPtr proxy = Private::InstantiateProxy();
		if ( !proxy )
			return NULL;

		if ( mc::IsFailed(proxy->Instantiate(protocol, clientId, server, mode, host)) )
			return NULL;

		return mc::ICommonPtr(proxy, mc::IID_ICommon);
	}

}
