#include "Common/Common.h"

#include "CommonKit/Project.h"

#include "AddRollback.h"

namespace Project
{

	AddRollback::AddRollback()
		: mc::CommandImpl()
#ifdef _COMPLIB
		, Components::ObjCounter()
#endif // _COMPLIB
		, container_()
		, item_()
	{
	}

	// ICommand section
	mc::result AddRollback::Configure(mc::DispParamsRef params)
	{
		assert( params );
		assert( params->Get(0) );
		assert( params->Get(1) );

		//container_ = IContainerWeak(IContainerPtr(params->Get(1)->toCommon(), IID_IContainer));
		container_ = GetWeak(IContainerPtr(params->Get(1)->toCommon(), IID_IContainer));
		item_ = params->Get(0)->toCommon();

		assert( item_ );

		return mc::_S_OK;
	} 

	mc::result AddRollback::Undo()
	{
		//IContainerPtr container(container_);
		IContainerPtr container = GetStrong(container_);
		
		if ( !container || !item_ )
			return mc::_E_INVALIDARG;

		container->Delete(item_);

		return mc::_S_OK;
	}

}
