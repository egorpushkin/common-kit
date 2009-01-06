#include "Common/Common.h"

#include "CommonKit/Project.h"

#include "Components/System/ComponentChecker.h"

#include "Components/Source/ComponentsManager.h"

namespace Components
{

	namespace Private
	{

		bool componentMode = true;

	}

	IComponentsManagerPtr GetComponentsManager()
	{
		if ( Private::componentMode )
		{
			IComponentPtr component(ComponentHolder::Instance().GetInstance(), IID_IComponent);
			if ( !component )
				return NULL;

			return component->GetCM();
		}
		else
		{
			return IComponentsManagerPtr(
				ComponentsManagerHolder::Instance().GetInstance(), 
				IID_IComponentsManager);
		}
	}

	mc::result SetCoreMode()
	{
		Private::componentMode = false;

		return mc::_S_OK;
	}

}
