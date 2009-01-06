#ifndef FACTORY_H__REMOTING__CORELIB__INCLUDED_
#define FACTORY_H__REMOTING__CORELIB__INCLUDED_

namespace Remoting
{

	mc::ICommonPtr InstantiateProxy(Network::IProtocolRef protocol, Network::IClient::Id_ clientId, IServerRef server, Behaviour mode, Network::IHostRef host);

}

#endif // !FACTORY_H__REMOTING__CORELIB__INCLUDED_
