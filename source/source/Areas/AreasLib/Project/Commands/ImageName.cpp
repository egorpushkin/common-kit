#include "Common/Common.h"

#include "ImageName.h"

namespace Areas
{

	ImageName::ImageName()
		: mc::CommandImpl()
		, Components::ObjCounter()
	{
	}

	// ICommand section
	mc::result ImageName::Undo()
	{
		assert( mc::CommandImpl::params_ );
		assert( mc::CommandImpl::params_->Get(1) );

		IMsImagePtr image(mc::CommandImpl::params_->Get(1)->toCommon(), IID_IMsImage);
		if ( !image )
			return mc::_E_INVALIDARG;

		mc::StringA imageName = mc::CommandImpl::params_->Get(0)->toStringA();

		image->SetSrcName(imageName);		

		return mc::_S_OK;
	}

}
