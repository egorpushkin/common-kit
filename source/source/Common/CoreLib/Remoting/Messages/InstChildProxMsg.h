#ifndef INSTCHILDPROXMSG_H__REMOTING__CORELIB__INCLUDED_
#define INSTCHILDPROXMSG_H__REMOTING__CORELIB__INCLUDED_

namespace Remoting
{

	class InstChildProxMsg
		: public InstChildMsg
	{
	public:

		InstChildProxMsg();

		InstChildProxMsg(void* objPtr, Network::IClient::Id_ clientId);

	};

}

#endif // !INSTCHILDPROXMSG_H__REMOTING__CORELIB__INCLUDED_
