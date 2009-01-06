#ifndef FILEFINDER_MAC_H__COMPONENTS__COMMONKIT__INCLUDED_
#define FILEFINDER_MAC_H__COMPONENTS__COMMONKIT__INCLUDED_

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

		DIR* dir_;

	};

}

#endif // !FILEFINDER_MAC_H__COMPONENTS__COMMONKIT__INCLUDED_
