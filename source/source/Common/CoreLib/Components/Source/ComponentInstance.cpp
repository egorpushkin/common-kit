#include "Common/Common.h"

#include "CommonKit/Components.h"

#include "CommonKit/Platform.h"

#include "Components/Source/ComponentInstance.h"

#include "Components/System/SharedObjects.h"

namespace Components
{

	ComponentInstance::ComponentInstance(const mc::StringA& fileName)
		: mc::CommonImpl< IComponentInstance >()
		, fileName_(fileName)
		, libraryHandle_(NULL)
		, pfnGetComponent_(NULL)
	{
	}

	ComponentInstance::~ComponentInstance()
	{
		if ( IsLoaded() )
		 	UnloadLibrary();
	}

	// ICommon section
	BEGIN_INTERFACE_MAP(ComponentInstance)
		COMMON(IComponentInstance)
		INTERFACE_(IComponentInstance, IID_IComponentInstance)
	END_INTERFACE_MAP()	

	// IComponentInstance section
	IComponentPtr ComponentInstance::ExtractComponent()
	{
		if ( mc::IsFailed(LoadComponent()) )
			return NULL;

		IComponentPtr component;
		mc::result code = (*pfnGetComponent_)(component);
		if ( mc::IsFailed(code) )
			return NULL;

		return component;
	}

	// Private tools
	mc::result ComponentInstance::LoadComponent()
	{
		if ( libraryHandle_ && pfnGetComponent_ )
			return mc::_S_FALSE;

		libraryHandle_ = SD_LoadLibrary(fileName_.c_str());
		if ( !libraryHandle_ )
			return mc::_E_FAIL; 

		pfnGetComponent_ = (PGET_COMPONENT)SD_GetProcAddress(libraryHandle_, "GetComponent");
		if ( !pfnGetComponent_ )
		{
			UnloadLibrary();
			return mc::_E_FAIL; 
		}

		return mc::_S_OK;
	}

	bool ComponentInstance::IsLoaded()
	{
		return ( libraryHandle_ != NULL );
	}

	void ComponentInstance::UnloadLibrary()
	{
		SD_FreeLibrary(libraryHandle_);
		pfnGetComponent_ = NULL;
	}

}
