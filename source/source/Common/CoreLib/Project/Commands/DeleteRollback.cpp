#include "Common/Common.h"

#include "CommonKit/Project.h"

#include "DeleteRollback.h"

namespace Project
{

	DeleteRollback::DeleteRollback()
		: mc::CommandImpl()
#ifdef _COMPLIB
		, Components::ObjCounter()
#endif // _COMPLIB
		, container_()
		, item_()
		, index_(0)
	{
	}

	// ICommand section
	mc::result DeleteRollback::Configure(mc::DispParamsRef params)
	{
		assert( params );
		assert( params->Get(1) );
		assert( params->Get(2) );

		//container_ = IContainerWeak(IContainerPtr(params->Get(2)->toCommon(), IID_IContainer));
		container_ = GetWeak(IContainerPtr(params->Get(2)->toCommon(), IID_IContainer));
		item_ = params->Get(1)->toCommon();
		index_ = params->Get(0)->toUInt();

		assert( item_ );

		return mc::_S_OK;
	} 

	mc::result DeleteRollback::Undo()
	{
		//IContainerPtr container(container_);
		IContainerPtr container = GetStrong(container_);

		if ( !container || !item_ )
			return mc::_E_INVALIDARG;

		container->InsertAfter(item_, index_);

		return mc::_S_OK; 
	}

}
