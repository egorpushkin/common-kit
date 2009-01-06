#include "Common/Common.h"

#include "InstMsg.h"

#include "Remoting/Messages/Codes.h"

namespace Remoting
{

	InstMsg::InstMsg()
		: Network::MessageImpl(MSGCODE_INST)
	{
		Network::MessageImpl::PutProperty(MSGPROP_OBJCLSID, mc::IID_Common);
	}

	InstMsg::InstMsg(mc::RefClsid clsid)
		: Network::MessageImpl(MSGCODE_INST)
	{
		Network::MessageImpl::PutProperty(MSGPROP_OBJCLSID, clsid);
	}

	// IMessage section
	Network::IMessage::Size_ InstMsg::GetDataSize()
	{
		return sizeof(mc::Clsid);
	}

	// MessageImpl section
	mc::result InstMsg::WriteBody(std::ostream& stream)
	{
		mc::Clsid clsid = Network::MessageImpl::GetProperty(MSGPROP_OBJCLSID).toGuid();
		
		stream.write((const char*)&clsid, sizeof(mc::Clsid));
		
		return mc::_S_OK;
	}

	mc::result InstMsg::ReadBody(std::istream& stream)
	{
		mc::Clsid clsid;
		
		stream.read((char*)&clsid, sizeof(mc::Clsid));
		
		Network::MessageImpl::PutProperty(MSGPROP_OBJCLSID, clsid);
		
		return mc::_S_OK;
	}

}
