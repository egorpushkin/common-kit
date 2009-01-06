#include "Common/Common.h"

namespace Remoting
{

	Response::Response(mc::IAgentRef remoteObjectAgent, mc::DispId idMember, mc::DispParamsRef params)
		: code_(mc::_E_FAIL)
		, retVal_(mc::ConstructVariantWrapper())
	{
		if ( remoteObjectAgent )
		{
			code_ = remoteObjectAgent->Invoke(idMember, params, retVal_);
		}
	}

	mc::Variant& Response::GetRetVal()
	{
		return retVal_->GetData();
	}

	bool IsFailed(ResponseRef response)
	{
		return mc::IsFailed(response->code_);
	}

	bool IsSucceeded(ResponseRef response)
	{
		return mc::IsSucceeded(response->code_);
	}

}

namespace MinCOM
{

	bool IsFailed(Remoting::ResponseRef response)
	{
		return Remoting::IsFailed(response);
	}

	bool IsSucceeded(Remoting::ResponseRef response)
	{
		return Remoting::IsSucceeded(response);
	}

}
