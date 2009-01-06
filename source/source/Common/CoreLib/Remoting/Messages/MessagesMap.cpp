#include "Common/Common.h"

#include "MessagesMap.h"

// Messages
#include "Remoting/Messages/Codes.h"
#include "Remoting/Messages/InstChildMsg.h"
#include "Remoting/Messages/InstChildDispMsg.h"
#include "Remoting/Messages/InstChildProxMsg.h"
#include "Remoting/Messages/InstMsg.h"
#include "Remoting/Messages/InstRespMsg.h"
#include "Remoting/Interfaces/IInvokeMsg.h"
#include "Remoting/Messages/InvokeMsg.h"
#include "Remoting/Messages/InvokeRespMsg.h"

namespace Remoting
{

	Network::IProtocolPtr MessagesMap::InstantiateProtocol()
	{
		Network::IProtocolPtr protocol = Network::InstantiateProtocol();
			
		if ( mc::IsFailed(Configure(protocol)) )
			return NULL;

		return protocol;
	}

	mc::IFactoryPtr MessagesMap::Prepare()
	{
		mc::IFactoryPtr messagesMap = mc::InstantiateFactory();
		if ( !messagesMap )
			return NULL;

		if ( mc::IsFailed(Configure(messagesMap)) )
			return NULL;

		return messagesMap;
	}

	mc::result MessagesMap::Configure(Network::IProtocolRef protocol)
	{
		if ( !protocol )
			return mc::_E_INVALIDARG;

		mc::IFactoryPtr messagesMap = protocol->GetMessagesMap();
		if ( !messagesMap )
		{
			protocol->SetMessagesMap(Prepare());
			return mc::_S_OK;
		}

		return Configure(messagesMap);
	}

	mc::result MessagesMap::Configure(mc::IFactoryRef messagesMap)
	{
		messagesMap->Register(MSGCODE_INSTCHILD_DISP, mc::ObjectCreator< InstChildDispMsg >);
		messagesMap->Register(MSGCODE_INSTCHILD_PROX, mc::ObjectCreator< InstChildProxMsg >);
		messagesMap->Register(MSGCODE_INST, mc::ObjectCreator< InstMsg >);
		messagesMap->Register(MSGCODE_INST_RESP, mc::ObjectCreator< InstRespMsg >);
		messagesMap->Register(MSGCODE_INVOKE, mc::ObjectCreator< InvokeMsg >);
		messagesMap->Register(MSGCODE_INVOKE_RESP, mc::ObjectCreator< InvokeRespMsg >);

		return mc::_S_OK;
	}

}
