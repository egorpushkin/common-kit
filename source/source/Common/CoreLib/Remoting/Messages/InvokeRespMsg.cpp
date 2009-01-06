#include "Common/Common.h"

#include "InvokeRespMsg.h"

#include "VariantStream.h"

#include "Remoting/Messages/Codes.h"

namespace Remoting
{

	InvokeRespMsg::InvokeRespMsg()
		: Network::MessageImpl(MSGCODE_INVOKE_RESP)
	{
		Network::MessageImpl::PutProperty(MSGPROP_RESPONSE, mc::_E_FAIL);
		Network::MessageImpl::PutProperty(MSGPROP_RETVAL, mc::Variant());
	}

	InvokeRespMsg::InvokeRespMsg(mc::result response, const mc::Variant& retVal)
		: Network::MessageImpl(MSGCODE_INVOKE_RESP)
	{
		Network::MessageImpl::PutProperty(MSGPROP_RESPONSE, response);
		Network::MessageImpl::PutProperty(MSGPROP_RETVAL, retVal);
	}

	// IMessage section
	Network::IMessage::Size_ InvokeRespMsg::GetDataSize()
	{
		return 
			sizeof(mc::result) + 
			VariantStream::SizeOf(Network::MessageImpl::GetProperty(MSGPROP_RETVAL));
	}

	// MessageImpl section
	mc::result InvokeRespMsg::WriteBody(std::ostream& stream)
	{
		mc::result response = Network::MessageImpl::GetProperty(MSGPROP_RESPONSE).toLong();
		
		stream.write((const char*)&response, sizeof(mc::result));		
		stream << Network::MessageImpl::GetProperty(MSGPROP_RETVAL);

		return mc::_S_OK;
	}

	mc::result InvokeRespMsg::ReadBody(std::istream& stream)
	{
		mc::result response = mc::_E_FAIL;
		mc::Variant retVal;

		stream.read((char*)&response, sizeof(mc::result));
		stream >> retVal;

		Network::MessageImpl::PutProperty(MSGPROP_RESPONSE, response);
		Network::MessageImpl::PutProperty(MSGPROP_RETVAL, retVal);

		return mc::_S_OK;
	}

}
