#ifndef COMPONENTIMPL_H__COMPONENTS__COMMONKIT__INCLUDED_
#define COMPONENTIMPL_H__COMPONENTS__COMMONKIT__INCLUDED_

namespace Components
{

	class ComponentImpl 
		: public mc::CommonImpl< IComponent >
		, public mc::CommonImpl< IInPlaceController >
		, public mc::APImpl
	{
	public:

		ComponentImpl(mc::RefIid typeIid, mc::RefIid iid);
		virtual ~ComponentImpl();

		// ICommon section
		DECLARE_INTERFACE_MAP()		

		// IComponent section
		virtual mc::Iid GetTypeIid();

		virtual mc::Iid GetIid();

		virtual mc::ICommonPtr CreateObject(mc::RefClsid clsid);

		virtual bool CanProduce(mc::RefClsid clsid);

		virtual mc::result Lock(bool lock);

		virtual mc::result SetCM(IComponentsManagerRef mc);

		virtual IComponentsManagerPtr GetCM();

		// IInPlaceController section
		virtual mc::result SendUnloadRequest();

	protected:

		// Protected tools
		bool Register(mc::RefClsid clsid, mc::CommonFactory::Creator_ creator);		
		
	private:

		mc::Iid typeIid_;
		
		mc::Iid iid_;

		IComponentsManagerWeak compMng_;

	};

}

#endif // !COMPONENTIMPL_H__COMPONENTS__COMMONKIT__INCLUDED_
