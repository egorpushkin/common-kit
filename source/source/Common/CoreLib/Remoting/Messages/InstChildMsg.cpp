#include "Common/Common.h"

#include "InstChildMsg.h"

#include "Remoting/Messages/Codes.h"

namespace Remoting
{

	InstChildMsg::InstChildMsg(Network::IMessage::Code_ code)
		: Network::MessageImpl(code)
	{
	}

	InstChildMsg::InstChildMsg(Network::IMessage::Code_ code, void* objPtr, Network::IClient::Id_ clientId)
		: Network::MessageImpl(code)
	{
		Network::MessageImpl::PutProperty(MSGPROP_OBJPTRID, objPtr);
		Network::MessageImpl::PutProperty(MSGPROP_CLIENTID, clientId);
	}

	// IMessage section
	Network::IMessage::Size_ InstChildMsg::GetDataSize()
	{
		return sizeof(void*) + sizeof(Network::IClient::Id_);
	}

	// MessageImpl section
	mc::result InstChildMsg::WriteBody(std::ostream& stream)
	{
		void* objPtr = Network::MessageImpl::GetProperty(MSGPROP_OBJPTRID).toPVoid();
		Network::IClient::Id_ clientId = Network::MessageImpl::GetProperty(MSGPROP_CLIENTID).toULong();
		
		stream.write((const char*)&objPtr, sizeof(void*));
		stream.write((const char*)&clientId, sizeof(Network::IClient::Id_));
		
		return mc::_S_OK;
	}

	mc::result InstChildMsg::ReadBody(std::istream& stream)
	{
		void* objPtr = NULL;
		Network::IClient::Id_ clientId = 0;
		
		stream.read((char*)&objPtr, sizeof(void*));
		stream.read((char*)&clientId, sizeof(Network::IClient::Id_));
		
		Network::MessageImpl::PutProperty(MSGPROP_OBJPTRID, objPtr);
		Network::MessageImpl::PutProperty(MSGPROP_CLIENTID, clientId);

		return mc::_S_OK;
	}

}
