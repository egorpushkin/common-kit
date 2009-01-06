#include "Common/Common.h"

mc::result GetComponent(Components::IComponentPtr& component)
{
	mc::ICommonPtr commonComponent = Components::ComponentHolder::Instance().GetInstance();

	if ( !commonComponent )
		return mc::_E_FAIL;

	component = Components::IComponentPtr(commonComponent, Components::IID_IComponent);

	if ( !component )
		return mc::_E_FAIL;

	return mc::_S_OK;
}
