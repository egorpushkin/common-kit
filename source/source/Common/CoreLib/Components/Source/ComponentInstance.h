#ifndef COMPONENTINSTANCE_H__COMPONENTS__COMMONKIT__INCLUDED_
#define COMPONENTINSTANCE_H__COMPONENTS__COMMONKIT__INCLUDED_

namespace Components
{

	typedef mc::result (*PGET_COMPONENT)(Components::IComponentPtr&);

	class ComponentInstance 
		: public mc::CommonImpl< IComponentInstance > 
	{
	public:

		ComponentInstance(const mc::StringA& fileName);
		virtual ~ComponentInstance();

		// ICommon section
		DECLARE_INTERFACE_MAP()		

		// IComponentInstance section
		virtual IComponentPtr ExtractComponent();


	private:

		mc::result LoadComponent();

		bool IsLoaded();

		void UnloadLibrary();



	private:

		mc::StringA fileName_;

		void* libraryHandle_;

		PGET_COMPONENT pfnGetComponent_;

	};

}

#endif // !COMPONENTINSTANCE_H__COMPONENTS__COMMONKIT__INCLUDED_
