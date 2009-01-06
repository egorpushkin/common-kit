#ifndef INSTCHILDDISPMSG_H__REMOTING__CORELIB__INCLUDED_
#define INSTCHILDDISPMSG_H__REMOTING__CORELIB__INCLUDED_

namespace Remoting
{

	class InstChildDispMsg
		: public InstChildMsg
	{
	public:

		InstChildDispMsg();

		InstChildDispMsg(void* objPtr, Network::IClient::Id_ clientId);

	};

}

#endif // !INSTCHILDMSG_H__REMOTING__CORELIB__INCLUDED_
