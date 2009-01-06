#include "Common/Common.h"

#include "InstRespMsg.h"

#include "Remoting/Messages/Codes.h"

namespace Remoting
{

	InstRespMsg::InstRespMsg()
		: Network::MessageImpl(MSGCODE_INST_RESP)
	{
		Network::MessageImpl::PutProperty(MSGPROP_CLIENTID, 0);
		Network::MessageImpl::PutProperty(MSGPROP_RESPONSE, mc::_E_FAIL);
	}

	InstRespMsg::InstRespMsg(Network::IClient::Id_ id, mc::result respose)
		: Network::MessageImpl(MSGCODE_INST_RESP)
	{
		Network::MessageImpl::PutProperty(MSGPROP_CLIENTID, id);
		Network::MessageImpl::PutProperty(MSGPROP_RESPONSE, respose);
	}

	// IMessage section
	Network::IMessage::Size_ InstRespMsg::GetDataSize()
	{
		return 
			sizeof(Network::IClient::Id_) +
			sizeof(mc::result);
	}

	// MessageImpl section
	mc::result InstRespMsg::WriteBody(std::ostream& stream)
	{
		Network::IClient::Id_ client = Network::MessageImpl::GetProperty(MSGPROP_CLIENTID).toULong();
		mc::result response = Network::MessageImpl::GetProperty(MSGPROP_RESPONSE).toLong();
		
		stream.write((const char*)&client, sizeof(Network::IClient::Id_));
		stream.write((const char*)&response, sizeof(mc::result));
		
		return mc::_S_OK;
	}

	mc::result InstRespMsg::ReadBody(std::istream& stream)
	{
		Network::IClient::Id_ client;
		mc::result response;

		stream.read((char*)&client, sizeof(Network::IClient::Id_));
		stream.read((char*)&response, sizeof(mc::result));

		Network::MessageImpl::PutProperty(MSGPROP_CLIENTID, client);
		Network::MessageImpl::PutProperty(MSGPROP_RESPONSE, response);

		return mc::_S_OK;
	}

}
