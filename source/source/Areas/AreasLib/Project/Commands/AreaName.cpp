#include "Common/Common.h"

#include "AreaName.h"

namespace Areas
{

	AreaName::AreaName()
		: mc::CommandImpl()
		, Components::ObjCounter()
	{
	}

	// ICommand section
	mc::result AreaName::Undo()
	{
		assert( mc::CommandImpl::params_ );
		assert( mc::CommandImpl::params_->Get(1) );

		IAreaPtr area(mc::CommandImpl::params_->Get(1)->toCommon(), IID_IArea);
		if ( !area )
			return mc::_E_INVALIDARG;

		area->SetName(
			mc::CommandImpl::params_->Get(0)->toStringA());

		return mc::_S_OK;
	}

}
