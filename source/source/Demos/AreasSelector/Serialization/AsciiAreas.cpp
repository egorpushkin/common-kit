#include "Common/Common.h"

#include "AsciiAreas.h"

#include <fstream>
#include <limits>

namespace Serialization
{

	AsciiAreas::AsciiAreas()
	{
	}

	AsciiAreas::~AsciiAreas()
	{
	}

	mc::result AsciiAreas::LoadProject(const mc::StringA& filename, Areas::IAProjectPtr& project)
	{
		project = NULL;

		std::ifstream ifs(filename.c_str());		
		if ( ifs.bad() || !ifs.is_open() )
			return mc::_E_FAIL;

		// Instantiate project
		mc::ICommonPtr cmpProject = Components::InstantiateCommon(Areas::LIBID_Areas, Areas::CLSID_AreasProject); 
		Project::IContainerPtr areasContainer(cmpProject, Project::IID_IContainer);

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
			mc::ICommonPtr cmnArea = Components::InstantiateCommon(Areas::LIBID_Areas, Areas::CLSID_Area); 
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
				mc::ICommonPtr cmnPoint = Components::InstantiateCommon(Areas::LIBID_Areas, Areas::CLSID_Point); 
				Areas::IPointPtr point = Areas::IPointPtr(cmnPoint, Areas::IID_IPoint);

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

		// Register constructed project as return target
		project = Areas::IAProjectPtr(cmpProject, Areas::IID_IAProject);

		return mc::_S_OK;
	}

	mc::result AsciiAreas::SaveProject(const mc::StringA& filename, Areas::IAProjectRef project)
	{
		return mc::_S_OK;
	}

}
