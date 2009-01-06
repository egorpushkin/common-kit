#ifndef LOCALLOADER_H__COMPONENTS__COMMONKIT__INCLUDED_
#define LOCALLOADER_H__COMPONENTS__COMMONKIT__INCLUDED_

namespace Components
{

	class FileFinder;
	
	typedef Loki::SmartPtr< FileFinder > FileFinderPtr;
	
	class LocalLoader
	{
	public:

		LocalLoader();
		
		~LocalLoader();

		IComponentInstancePtr LoadComponent(mc::RefIid iid, ComponentChecker::Method_ method, mc::RefIid typeIid = TYPEID_General);

	private:

		IComponentInstancePtr LocalLoader::LoadFirst();
		
		IComponentInstancePtr LocalLoader::LoadNext();
		
	protected:
	
		virtual IComponentInstancePtr InstanceFromFileName(const mc::StringA& fileName, bool hasFile);
		
		virtual mc::StringA PrepareFolderPattern();

	private:

		FileFinderPtr finderTool_;

		mc::StringA folderName_;

	};

}

#endif // !COMPONENTSMANAGER_H__COMPONENTS__COMMONKIT__INCLUDED_
