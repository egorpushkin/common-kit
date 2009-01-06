#include "Common/Common.h"

#include "WidgetImpl.h"

namespace Selector
{

	WidgetImpl::WidgetImpl()
		: mc::CommonImpl< IWidget >()
		, behaviour_()
	{
	}

	// ICommon section
	BEGIN_INTERFACE_MAP(WidgetImpl)
		COMMON(IWidget)
		INTERFACE(IWidget)
	END_INTERFACE_MAP()

	// IWidget section
	mc::result WidgetImpl::SetBehaviour(IBehaviourRef behaviour)
	{
		behaviour_ = behaviour;

		return mc::_S_OK;
	}

	IBehaviourPtr WidgetImpl::GetBehaviour()
	{
		return behaviour_;
	}

}
