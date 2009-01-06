#include "Common/Common.h"

#include "Remoting/Interfaces/IInvokeMsg.h"

#include "InvokeMsg.h"

#include "VariantStream.h"

#include "Remoting/Messages/Codes.h"

namespace Remoting
{

	InvokeMsg::InvokeMsg()
		: mc::CommonImpl< IInvokeMsg >()
		, Network::MessageImpl(MSGCODE_INVOKE)
		, dispParams_()
	{
		Network::MessageImpl::PutProperty(MSGPROP_DISPID, 0);
		Network::MessageImpl::PutProperty(MSGPROP_IID, mc::IID_IAgent);
	}

	InvokeMsg::InvokeMsg(mc::DispId idMember, mc::DispParamsRef dispParams, mc::RefIid iid)
		: mc::CommonImpl< IInvokeMsg >()
		, Network::MessageImpl(MSGCODE_INVOKE)
		, dispParams_(dispParams)
	{
		Network::MessageImpl::PutProperty(MSGPROP_DISPID, idMember);
		Network::MessageImpl::PutProperty(MSGPROP_IID, iid);
	}

	// ICommon section
	BEGIN_INTERFACE_MAP(InvokeMsg)
		COMMON(IInvokeMsg)
		INTERFACE(IInvokeMsg)
		IMPL(Network::MessageImpl)
	END_INTERFACE_MAP()		

	// IInvokeMessage section
	void InvokeMsg::SetParams(mc::DispParamsRef dispParams)
	{
		dispParams_ = dispParams;
	}

	mc::DispParamsPtr InvokeMsg::GetParams()
	{
		return dispParams_;
	}

	// IMessage section
	Network::IMessage::Size_ InvokeMsg::GetDataSize()
	{
		return 
			sizeof(mc::DispId) + 
			sizeof(mc::Iid) + 
			sizeof(unsigned int) + 
			GetParamsSize();
	}

	// MessageImpl section
	mc::result InvokeMsg::WriteBody(std::ostream& stream)
	{
		// Send invoke id
		mc::DispId dispId = Network::MessageImpl::GetProperty(MSGPROP_DISPID).toLong();
		stream.write((const char*)&dispId, sizeof(mc::DispId));

		// Send iid 
		mc::Iid iid = Network::MessageImpl::GetProperty(MSGPROP_IID).toGuid();
		stream.write((const char*)&iid, sizeof(mc::Iid));		

		// Send params count
		unsigned int paramsCount = 0;
		if ( dispParams_ )
			paramsCount = dispParams_->GetCount();		
		stream.write((const char*)&paramsCount, sizeof(unsigned int));

		// Send params
		for ( unsigned int i = 0 ; i < paramsCount ; ++i )
			stream << *dispParams_->Get(i);
		
		return mc::_S_OK;
	}

	mc::result InvokeMsg::ReadBody(std::istream& stream)
	{
		// Read invoke id
		mc::DispId dispId = 0;
		stream.read((char*)&dispId, sizeof(mc::DispId));
		Network::MessageImpl::PutProperty(MSGPROP_DISPID, dispId);

		// Read iid
		mc::Iid iid;
		stream.read((char*)&iid, sizeof(mc::Iid));
		Network::MessageImpl::PutProperty(MSGPROP_IID, iid);

		// Read params count
		unsigned int paramsCount = 0;
		stream.read((char*)&paramsCount, sizeof(unsigned int));
		dispParams_ = mc::CreateParamsCore(paramsCount);

		// Read params
		for ( unsigned int i = 0 ; i < paramsCount ; ++i )
			stream >> dispParams_->GetRef(i);
		
		return mc::_S_OK;
	}

	// Private tools
	Network::IMessage::Size_ InvokeMsg::GetParamsSize()
	{
		if ( !dispParams_ )
			return 0;

		Network::IMessage::Size_ size = 0;

		unsigned int paramsCount = dispParams_->GetCount();	
		for ( unsigned int i = 0 ; i < paramsCount ; ++i )
			size += VariantStream::SizeOf(*dispParams_->Get(i));

		return 0;
	}

}
