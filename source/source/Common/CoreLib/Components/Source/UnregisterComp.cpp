#include "Common/Common.h"

#include "CommonKit/Components.h"

#include "CommonKit/Project.h"

#include "UnregisterComp.h"

namespace Components
{

	UnregisterComp::UnregisterComp()
		: mc::AgentImpl()
	{
	}

	UnregisterComp::~UnregisterComp()
	{
	}

	// IAgent section
	mc::result UnregisterComp::Invoke(mc::DispId idMember, mc::DispParamsRef dispParams, mc::IVariantWrapperRef /* result */, mc::RefIid /* iid */)
	{		

		if ( idMember == AGENTID_MAINJOBCALL )
		{
			// Add forced delay to prevent unloading during stack collapsing.
			// This operation skipped due to starting jobs' context queue with lowest prioroty.
			// 
			mc::IEventPtr delayEvent = mc::InstantiateEvent();
			delayEvent->Wait(256);
			//

			// Acquire params
			IComponentsManagerPtr componentsMng(dispParams->Get(1)->toCommon(), IID_IComponentsManager);
			mc::Iid compIid = dispParams->Get(0)->toGuid();

			if ( !componentsMng )
				return mc::_E_FAIL;

			componentsMng->UnregisterComponent(compIid);
		}

		return mc::_S_OK;
	}

}