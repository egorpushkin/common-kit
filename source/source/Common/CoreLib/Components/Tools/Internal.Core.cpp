#include "Common/Common.h"

#include "CommonKit/Project.h"

#include "Components/System/ComponentChecker.h"

#include "Components/Source/ComponentsManager.h"

namespace Components
{

	IComponentsManagerPtr GetComponentsManager()
	{
		return IComponentsManagerPtr(
			ComponentsManagerHolder::Instance().GetInstance(), 
			IID_IComponentsManager);
	}

}
