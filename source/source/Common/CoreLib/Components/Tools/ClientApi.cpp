#include "Common/Common.h"

#include "CommonKit/Components.h"

#include "CommonKit/Project.h"

#include "Components/System/ComponentChecker.h"

#include "Components/Source/ComponentsManager.h"

namespace Components
{

	mc::ICommonPtr InstantiateCommon(mc::RefClsid objId)
	{
		// Delegate call to components manager
		IComponentsManagerPtr compMng = GetComponentsManager();

		if ( !compMng )
			return NULL;

		return compMng->InstantiateCommon(objId);
	}

	mc::ICommonPtr InstantiateCommon(mc::RefIid libIid, mc::RefClsid objId)
	{
		// Delegate call to components manager
		IComponentsManagerPtr compMng = GetComponentsManager();

		if ( !compMng )
			return NULL;

		return compMng->InstantiateCommon(libIid, objId);
	}

}
