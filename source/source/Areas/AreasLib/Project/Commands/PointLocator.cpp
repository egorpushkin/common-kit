#include "Common/Common.h"

#include "PointLocator.h"

namespace Areas
{

	PointLocator::PointLocator()
		: mc::CommandImpl()
		, Components::ObjCounter()
	{
	}

	// ICommand section
	mc::result PointLocator::Undo()
	{
		assert( mc::CommandImpl::params_ );
		assert( mc::CommandImpl::params_->Get(2) );

		IPointPtr point(mc::CommandImpl::params_->Get(2)->toCommon(), IID_IPoint);
		if ( !point )
			return mc::_E_INVALIDARG;

		point->SetLocation(
			mc::CommandImpl::params_->Get(1)->toDouble(),
			mc::CommandImpl::params_->Get(0)->toDouble());

		return mc::_S_OK;
	}

}
