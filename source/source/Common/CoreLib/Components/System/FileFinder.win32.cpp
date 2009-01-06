#include "Common/Common.h"

#include <io.h>

#include "FileFinder.win32.h"

namespace Components
{

	FileFinder::FileFinder()
		: fileInfo_()
		, searchDone_()
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
		
		searchDone_ = _findfirst(folderPattern.c_str(), &fileInfo_);	
		if ( searchDone_ == -1 )
			return false;
			
		fileName = mc::StringA(fileInfo_.name);
		return true;	
	}
		
	bool FileFinder::FindNext(mc::StringA& fileName)
	{
		int done = _findnext(searchDone_, &fileInfo_);
		if (done == -1)
		{
			FindClose();
			return NULL;
		}
			
		fileName = mc::StringA(fileInfo_.name);
		return true;
	}
	
	void FileFinder::FindClose()
	{
		_findclose(searchDone_);
	}

}
