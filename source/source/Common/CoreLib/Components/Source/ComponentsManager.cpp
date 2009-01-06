#include "Common/Common.h"

#include "CommonKit/Components.h"

#include "CommonKit/Project.h"

#include "Components/System/ComponentChecker.h"

#include "Components/Source/ComponentsManager.h"

#include "Components/System/LocalLoader.h"

#include "JobsQueue.h"

#include "UnregisterComp.h"

namespace Components
{

	ComponentsManager::ComponentsManager()
		: mc::CommonImpl< IComponentsManager >()
		, mc::AgentImpl()
		, mc::ItemImpl()
		, mc::CookiesHelper()
		, lock_(mc::InstantiateMutex())
		, jobs_(InstantiateJobsQueue())
		, components_(Container::CreateUnmanagedDefault< mc::ICommonPtr >())
	{
		jobs_->Start();
	}

	ComponentsManager::~ComponentsManager()
	{
		// jobs_->Stop();
	}

	// ICommon section
	BEGIN_INTERFACE_MAP(ComponentsManager)
		COMMON(IComponentsManager)
		INTERFACE_(IComponentsManager, IID_IComponentsManager)
		IMPL(mc::AgentImpl)
		IMPL(mc::ItemImpl)
	END_INTERFACE_MAP()	

	// IComponentsManager section
	mc::ICommonPtr ComponentsManager::InstantiateCommon(mc::RefClsid clsid)
	{
		mc::MutexLock lock(lock_);

		return InstantiateCommon(clsid, clsid, ComponentChecker::METHOD_BYCLSID_);
	}

	mc::ICommonPtr ComponentsManager::InstantiateCommon(mc::RefIid libIid, mc::RefClsid clsid)
	{
		mc::MutexLock lock(lock_);

		return InstantiateCommon(clsid, libIid, ComponentChecker::METHOD_BYLIBIID_);
	}

	mc::ICommonPtr ComponentsManager::InstantiateByTypeIid(mc::RefIid typeIid, mc::RefClsid clsid)
	{
		mc::MutexLock lock(lock_);

		return InstantiateCommon(clsid, clsid, ComponentChecker::METHOD_BYLIBTYPE_, typeIid);
	}

	mc::result ComponentsManager::UnregisterComponent(mc::RefIid iid)
	{
		mc::MutexLock lock(lock_);

		IComponentInstancePtr componentInstance = FindInstance(iid);
		if ( !componentInstance )
			return mc::_E_INVALIDARG;

		// Remove instance from list first
		components_->Delete(mc::ICommonPtr(componentInstance, mc::IID_ICommon));

		{

			IComponentPtr component = componentInstance->ExtractComponent();
			if ( !component )
				return mc::_E_INVALIDARG;

			mc::ICommonPtr cmnComponent(component, mc::IID_ICommon);
			if ( !cmnComponent )
				return mc::_E_INVALIDARG;

			// Unadvise manager from component's events
			mc::Unadvise(cmnComponent, mc::CookiesHelper::GetCookie(cmnComponent));

			// Unregister at cookies helper
			mc::CookiesHelper::Unregister(cmnComponent);

		}

		// At the moment the only reference to loaded instance is held by local pointer 
		// declared withing the scope of this function. 
		// Corresponding object will be removed during stack collapsing and this will cause 
		// unloading of dynamic library.

		return mc::_S_OK;
	}

	IJobsQueuePtr ComponentsManager::GetJobs()
	{
		mc::MutexLock lock(lock_);

		return jobs_;
	}

	// IAgent section
	mc::result ComponentsManager::Invoke(mc::DispId idMember, mc::DispParamsRef dispParams, mc::IVariantWrapperRef /* result */, mc::RefIid /* iid */)
	{		
		mc::MutexLock lock(lock_);

		if ( idMember == AGENTID_UNLOADME )
		{
			IComponentPtr component(dispParams->Get(0)->toCommon(), IID_IComponent);
			if ( !component )
				return mc::_E_FAIL;

			// Trainslate component's reference into unique iid
			mc::Guid guid = component->GetIid();

			// Unregister component asynchronously
			jobs_->Push(
				mc::InstantiateAgent< UnregisterComp >(),
				mc::CreateParams(
					mc::ItemImpl::GetLocal(),			// Param 1: Manager
					guid								// Param 2: Component's iid
				)
			);
        }

		return mc::_S_OK;
	}

	// Private tools
	mc::ICommonPtr ComponentsManager::InstantiateCommon(mc::RefClsid clsid, mc::RefIid iid, ComponentChecker::Method_ method, mc::RefIid typeIid)
	{
		// Check whether required component has been already loaded
		mc::ICommonPtr object = TryConstructLocally(clsid, iid, method);
		if ( object )
			return object;

		return TryConstructGlobally(clsid, iid, method, typeIid);
	}

	mc::ICommonPtr ComponentsManager::TryConstructLocally(mc::RefClsid clsid, mc::RefIid iid, ComponentChecker::Method_ method)
	{
		mc::ICommonPtr resultObject;

		ComponentChecker checker(method);

		Container::ICommonEnumPtr cmnInstances = components_->Clone();
		for ( bool hasInst = cmnInstances->SelectFirst() ; hasInst ; hasInst = cmnInstances->SelectNext() )
		{
			IComponentInstancePtr componentInstance(cmnInstances->GetSelected(), IID_IComponentInstance);
			if ( !componentInstance )
				continue;

			IComponentPtr component = componentInstance->ExtractComponent();
			if ( !component )
				continue;

			if ( !checker.Check(component, iid) )
				continue;

			resultObject = component->CreateObject(clsid);
			if ( resultObject )
				break;
		}

		return resultObject;
	}

	mc::ICommonPtr ComponentsManager::TryConstructGlobally(mc::RefClsid clsid, mc::RefIid iid, ComponentChecker::Method_ method, mc::RefIid typeIid)
	{
		LocalLoader loader;
		IComponentInstancePtr componentInstance = loader.LoadComponent(iid, method, typeIid);
		if ( !componentInstance )
			return NULL;

		IComponentPtr component = componentInstance->ExtractComponent();
		if ( !component )
			return NULL;

		component->SetCM(GetComponentsManager());

		// Try to instantiate object
		mc::ICommonPtr object = component->CreateObject(clsid);
		if ( !object )
			return NULL; 

		// Register component
		components_->Add(mc::ICommonPtr(componentInstance, mc::IID_ICommon));

		// Advise manager on component's events
		unsigned long cookie = 0;

		mc::ICommonPtr connecteeCommon(component, mc::IID_ICommon);

		mc::result code = mc::Advise(connecteeCommon, mc::ItemImpl::GetLocal(), cookie);
		if ( mc::IsSucceeded(code) )
		{
			// Remember cookie to use it when it happens to remove point
			mc::CookiesHelper::Register(connecteeCommon, cookie);
		}

		// Return created object
		return object;	
	}

	IComponentInstancePtr ComponentsManager::FindInstance(mc::RefIid iid)
	{
		Container::ICommonEnumPtr instances = components_->Clone();

		for ( bool hasItems = instances->SelectFirst() ; hasItems ; hasItems = instances->SelectNext() )
		{
			IComponentInstancePtr instance(instances->GetSelected(), IID_IComponentInstance);
			if ( !instance )
				continue;

			IComponentPtr component = instance->ExtractComponent();
			if ( !component )
				continue;
			
			if ( component->GetIid() == iid )
				return instance;
		}	

		return NULL;
	}

	// Creator
	ComponentsManagerCreator::ComponentsManagerCreator()
		: CommonHolder_()
	{
	}

	ComponentsManagerCreator::~ComponentsManagerCreator()
	{
		// Must implement exception safe destructor
		try
		{
			// Must prevent momentary manager destruction

			// Acquire component's jobs
			IJobsQueuePtr jobs = GetComponentsManager()->GetJobs();
			if ( !jobs )
				// There is no worker to wait for
				return;

			jobs->Stop();

			// And allow system to delete this object. This will cause releasing 
			// components manager.
		}
		catch ( ... ) 
		{
		}
	}

}