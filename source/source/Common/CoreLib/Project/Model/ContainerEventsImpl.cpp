#include "Common/Common.h"

#include "CommonKit/Project.h"

namespace Project
{

	ContainerEventsImpl::ContainerEventsImpl()
		: mc::CommonImpl< IContainerEvents >()
		, onBeforeAdd_(AGENTID_ADDINGITEM)
		, onAfterAdd_(AGENTID_ITEMADDED)		
		, onBeforeDelete_(AGENTID_DELETINGITEM)	
		, onAfterDelete_(AGENTID_ITEMDELETED)	
	{
	}

	// ICommon section
	BEGIN_INTERFACE_MAP(ContainerEventsImpl)
		COMMON(IContainerEvents)
		INTERFACE(IContainerEvents)
	END_INTERFACE_MAP()

	// IContainer section
	void ContainerEventsImpl::SetOnBeforeAdd(mc::DispId id)
	{
		onBeforeAdd_ = id;
	}

	void ContainerEventsImpl::SetOnAfterAdd(mc::DispId id)
	{
		onAfterAdd_ = id;
	}

	void ContainerEventsImpl::SetOnBeforeDelete(mc::DispId id)
	{
		onBeforeDelete_ = id;
	}

	void ContainerEventsImpl::SetOnAfterDelete(mc::DispId id)
	{
		onAfterDelete_ = id;
	}

	mc::DispId ContainerEventsImpl::GetOnBeforeAdd()
	{
		return onBeforeAdd_;
	}

	mc::DispId ContainerEventsImpl::GetOnAfterAdd()
	{
		return onAfterAdd_;
	}

	mc::DispId ContainerEventsImpl::GetOnBeforeDelete()
	{
		return onBeforeDelete_;
	}

	mc::DispId ContainerEventsImpl::GetOnAfterDelete()
	{
		return onAfterDelete_;
	}

}
