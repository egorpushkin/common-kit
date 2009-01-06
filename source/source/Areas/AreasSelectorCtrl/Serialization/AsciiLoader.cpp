#include "Common/Common.h"

#include "AsciiLoader.h"

#include <fstream>
#include <limits>

namespace Serialization
{

	AsciiLoader::AsciiLoader()
		: mc::CommonImpl< AreasSelector::ILoader >()
	{
	}

	// ICommon section
	BEGIN_INTERFACE_MAP(AsciiLoader)
		COMMON(AreasSelector::ILoader)
		INTERFACE_(AreasSelector::ILoader, AreasSelector::IID_ILoader)
	END_INTERFACE_MAP()

	// ILoader section
	mc::result AsciiLoader::LoadProject(const mc::StringA& filename, Areas::IAProjectPtr& project)
	{
		project = NULL;

		std::ifstream ifs(filename.c_str());		
		if ( ifs.bad() || !ifs.is_open() )
			return mc::_E_FAIL;

		// Instantiate project
		mc::ICommonPtr cmpProject = Components::InstantiateCommon(Areas::CLSID_AreasProject); 
		Project::IContainerPtr areasContainer(cmpProject, Project::IID_IContainer);

		// Commands container
		mc::ICommandsPtr commands;

		// Acquire project item
		mc::IItemPtr projectItem(cmpProject, mc::IID_IItem);
		if ( projectItem )
		{
			// Acquire commands manager
			commands = mc::ICommandsPtr(projectItem->Acquire(mc::CLSID_Commands), mc::IID_ICommands);
		}

		if ( commands )
		{
			// Disable manager
			commands->Enable(false);
		}

		// Parse format
		//////////////////////////////////////////////////////////////////////////
		
		// Skip first line
		ifs.ignore(std::numeric_limits<int>::max(), '\n');

		// Read a number of areas
		unsigned int areasCount;
		ifs >> areasCount;

		// Skip line after reading number
		ifs.ignore(std::numeric_limits<int>::max(), '\n');

		// Skip comments line
		ifs.ignore(std::numeric_limits<int>::max(), '\n');

		// Read areas
		for ( unsigned int i = 0 ; i < areasCount ; ++i )
		{
			// Instantiate area
			mc::ICommonPtr cmnArea = Components::InstantiateCommon(Areas::CLSID_Area); 
			Project::IContainerPtr pointsContainer(cmnArea, Project::IID_IContainer);

			// Skip comments line
			ifs.ignore(std::numeric_limits<int>::max(), '\n');
			// Skip area name
			ifs.ignore(std::numeric_limits<int>::max(), '\n');
			// Skip comments line
			ifs.ignore(std::numeric_limits<int>::max(), '\n');

			// Read a number of points
			unsigned int pointsCount;
			ifs >> pointsCount;

			// Skip line after reading number
			ifs.ignore(std::numeric_limits<int>::max(), '\n');

			// Skip comments line
			ifs.ignore(std::numeric_limits<int>::max(), '\n');

			for ( unsigned int j = 0 ; j < pointsCount ; ++j )
			{
				// Instantiate point
				mc::ICommonPtr cmnPoint = Components::InstantiateCommon(Areas::CLSID_Point); 
				
				Areas::IPointPtr point(cmnPoint, Areas::IID_IPoint);
				if ( !point )
					continue;

				// Load point's location
				unsigned int x, y;
				ifs >> x;
				ifs >> y;

				// Specify location
				point->SetLocation(x, y);

				// Add constructed and configured point
				pointsContainer->Add(cmnPoint);
			}

			// Skip line after reading number
			ifs.ignore(std::numeric_limits<int>::max(), '\n');

			// Add constructed area
			areasContainer->Add(cmnArea);
		}

		if ( commands )
		{
			// Enable manager
			commands->Enable(true);

			// Set state to unmodified
			commands->SetModified(false);
		}

		// Register constructed project as return target
		project = Areas::IAProjectPtr(cmpProject, Areas::IID_IAProject);

		return mc::_S_OK;
	}

	mc::result AsciiLoader::SaveProject(const mc::StringA& filename, Areas::IAProjectRef project)
	{
		if ( !project )
			return mc::_E_INVALIDARG;

		std::ofstream ofs(filename.c_str());		
		if ( ofs.bad() || !ofs.is_open() )
			return mc::_E_FAIL;

		// Acquire areas container
		Project::IContainerPtr areasContainer(project, Project::IID_IContainer);

		ofs << "# Areas count" << std::endl;

		// Acquire areas
		Container::ICommonEnumPtr areasEnum = areasContainer->GetItems();

		// Dump a number of areas
		ofs << areasEnum->GetTotal() << std::endl;

		ofs << "# Enumerating areas" << std::endl;

		// Dump areas
		int i = 1;
		for ( 
			bool hasArea = areasEnum->SelectFirst() ; 
			hasArea ; 
			hasArea = areasEnum->SelectNext(), ++i )
		{
			ofs << "## 'Area " << i << "'" << std::endl;
			ofs << "Area " << i << std::endl;
			ofs << "## 'Area " << i << "': Points count" << std::endl;

			// Acquire points container
			Project::IContainerPtr pointsContainer(areasEnum->GetSelected(), Project::IID_IContainer);
			if ( !pointsContainer )
				continue;

			// Acquire points
			Container::ICommonEnumPtr pointsEnum = pointsContainer->GetItems();

			// Dump a number of points
			ofs << pointsEnum->GetTotal() << std::endl;
			
			ofs << "## 'Area " << i << "': Enumerating points" << std::endl;

			for ( bool hasPoint = pointsEnum->SelectFirst() ; hasPoint ; hasPoint = pointsEnum->SelectNext() )
			{	
				Areas::IPointPtr point(pointsEnum->GetSelected(), Areas::IID_IPoint);
				if ( !point )
					continue;
	
				ofs << point->GetX() << " " << point->GetY() << std::endl;
			}
		}

		// Update project's state to unmodified
		mc::IItemPtr projectItem(project, mc::IID_IItem);
		if ( projectItem )
		{
			mc::ICommandsPtr commands(
				projectItem->Acquire(mc::CLSID_Commands), 
				mc::IID_ICommands);

			if ( commands )
				commands->SetModified(false);
		}		

		return mc::_S_OK;
	}

}
