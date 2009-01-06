#include "Common/Common.h"

#include "InstChildMsg.h"
#include "InstChildDispMsg.h"

#include "Remoting/Messages/Codes.h"

namespace Remoting
{

	InstChildDispMsg::InstChildDispMsg()
		: InstChildMsg(MSGCODE_INSTCHILD_DISP)
	{
	}

	InstChildDispMsg::InstChildDispMsg(void* objPtr, Network::IClient::Id_ clientId)
		: InstChildMsg(MSGCODE_INSTCHILD_DISP)
	{
		Network::MessageImpl::PutProperty(MSGPROP_OBJPTRID, objPtr);
		Network::MessageImpl::PutProperty(MSGPROP_CLIENTID, clientId);
	}

}
