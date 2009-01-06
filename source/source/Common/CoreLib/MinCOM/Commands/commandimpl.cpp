#include "Common/Common.h"

namespace MinCOM
{

	CommandImpl::CommandImpl()
		: CommonImpl< ICommand >()
		, params_()
	{
	}

	// ICommon section
	BEGIN_INTERFACE_MAP(CommandImpl)
		COMMON(ICommand)
		INTERFACE(ICommand)
	END_INTERFACE_MAP()

	// ICommand section
	result CommandImpl::Configure(DispParamsRef params)
	{
		params_ = params;

		return _S_OK;
	}

	result CommandImpl::Undo()
	{
		return _E_NOTIMPL;
	}

}
