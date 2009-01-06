#include "Common/Common.h"

#include "InstChildMsg.h"
#include "InstChildProxMsg.h"

#include "Remoting/Messages/Codes.h"

namespace Remoting
{

	InstChildProxMsg::InstChildProxMsg()
		: InstChildMsg(MSGCODE_INSTCHILD_PROX)
	{
	}

	InstChildProxMsg::InstChildProxMsg(void* objPtr, Network::IClient::Id_ clientId)
		: InstChildMsg(MSGCODE_INSTCHILD_PROX)
	{
		Network::MessageImpl::PutProperty(MSGPROP_OBJPTRID, objPtr);
		Network::MessageImpl::PutProperty(MSGPROP_CLIENTID, clientId);
	}

}
