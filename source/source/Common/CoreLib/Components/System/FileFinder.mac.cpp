#include "Common/Common.h"

#include <dirent.h>

#include "FileFinder.mac.h"

namespace Components
{

	FileFinder::FileFinder()
		: dir_(NULL)
	{
	}
	
	FileFinder::~FileFinder()
	{
		FindClose();
	}

	bool FileFinder::FindFirst(const mc::StringA& folderPattern, mc::StringA& fileName)
	{
		// Destroy previous search handles
		FindClose();
		
		if( (dir_ = opendir(folderPattern.c_str())) == NULL ) 
			return false;
			
		return FindNext(fileName);	
	}
		
	bool FileFinder::FindNext(mc::StringA& fileName)
	{
		if ( !dir_ )
			return false;
			
		struct dirent* dirItem = readdir(dir_);
		if ( !dirItem )
		{
			FindClose();
			return false;
		}
			
		fileName = mc::StringA(dirItem->d_name);
		return true;
	}
	
	void FileFinder::FindClose()
	{
		if ( dir_ )
			closedir(dir_);
			
		dir_ = NULL;
	}

}