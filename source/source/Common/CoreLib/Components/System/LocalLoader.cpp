#include "Common/Common.h"

#include "CommonKit/Components.h"

#include "ComponentChecker.h"

#include "LocalLoader.h"

#include "Components/Source/ComponentInstance.h"

//R12_MAC_PORT
#ifdef _MSC_VER
#include <io.h>
#include "FileFinder.win32.h"
#else 
#include <dirent.h>
#include "FileFinder.mac.h"
#endif

#include "Components/System/SharedObjects.h"

namespace Components
{

	LocalLoader::LocalLoader()
		: finderTool_(new FileFinder())
		, folderName_(".")
	{
	}
	
	LocalLoader::~LocalLoader()
	{
	}

	IComponentInstancePtr LocalLoader::LoadComponent(mc::RefIid iid, ComponentChecker::Method_ method, mc::RefIid typeIid)
	{
		ComponentChecker checker(method);

		for (
			IComponentInstancePtr instance = LoadFirst() ;
			instance ;
			instance = LoadNext() )
		{
			IComponentPtr component = instance->ExtractComponent();
			if ( !component )
				continue;

			if ( checker.Check(component, iid, typeIid) )
				return instance;
		}

		return NULL;
	}	

	// Private tools
	IComponentInstancePtr LocalLoader::LoadFirst()
	{
		mc::StringA libraryName;
		bool hasFile = finderTool_->FindFirst(PrepareFolderPattern(), libraryName);	
		return InstanceFromFileName(libraryName, hasFile);
	}

	IComponentInstancePtr LocalLoader::LoadNext()
	{
		mc::StringA libraryName;
		bool hasFile = finderTool_->FindNext(libraryName);	
		return InstanceFromFileName(libraryName, hasFile);
	}
	
	IComponentInstancePtr LocalLoader::InstanceFromFileName(const mc::StringA& fileName, bool hasFile)
	{
		if ( !hasFile )
			return NULL;
	
		mc::StringA filePath =
			folderName_ + 
			mc::StringA("/") + 
			fileName;

		return IComponentInstancePtr(
			new ComponentInstance(filePath),
			IID_IComponentInstance);
	}
	
	mc::StringA LocalLoader::PrepareFolderPattern()
	{
		mc::StringA folderPattern =
			folderName_ + 
			mc::StringA("/*") + 
			SO_LIB_EXT;
			
		return folderPattern;
	}

}
