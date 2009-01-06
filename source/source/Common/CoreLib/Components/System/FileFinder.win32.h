#ifndef FILEFINDER_WIN32_H__COMPONENTS__COMMONKIT__INCLUDED_
#define FILEFINDER_WIN32_H__COMPONENTS__COMMONKIT__INCLUDED_

namespace Components
{

	class FileFinder
	{
	public:

		FileFinder();
		
		~FileFinder();

		bool FindFirst(const mc::StringA& folderPattern, mc::StringA& fileName);
		
		bool FindNext(mc::StringA& fileName);
		
	private:
	
		void FindClose();

	private:

		_finddata_t fileInfo_;

		intptr_t searchDone_;

	};

}

#endif // !FILEFINDER_WIN32_H__COMPONENTS__COMMONKIT__INCLUDED_
