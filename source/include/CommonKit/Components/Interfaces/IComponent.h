#ifndef ICOMPONENT_H__COMPONENTS__COMMONKIT__INCLUDED_
#define ICOMPONENT_H__COMPONENTS__COMMONKIT__INCLUDED_

namespace Components
{

	interface IComponentsManager;
	typedef mc::ComPtr< IComponentsManager > IComponentsManagerPtr;
	typedef const IComponentsManagerPtr& IComponentsManagerRef;
	typedef mc::ComPtr< IComponentsManager, false > IComponentsManagerWeak;

	interface IComponent : public mc::ICommon
	{
		
		virtual mc::Iid GetTypeIid() = 0;
		
		virtual mc::Iid GetIid() = 0;

		virtual mc::ICommonPtr CreateObject(mc::RefClsid clsid) = 0;

		virtual bool CanProduce(mc::RefClsid clsid) = 0;

		virtual mc::result Lock(bool lock) = 0;

		virtual mc::result SetCM(IComponentsManagerRef mc) = 0;

		virtual IComponentsManagerPtr GetCM() = 0;

	};

	typedef mc::ComPtr< IComponent > IComponentPtr;
	typedef const IComponentPtr& IComponentRef;

	// {fba1b349-b99d-456c-b878-5790ce32e606} 
	MC_DEFINE_GUID(IID_IComponent, 
	0xfba1b349, 0xb99d, 0x456c, 0xb8, 0x78, 0x57, 0x90, 0xce, 0x32, 0xe6, 0x06);

	// Component events
	enum
	{
		AGENTID_UNLOADME = 0xff01000A
	};

}

#endif // !ICOMPONENT_H__COMPONENTS__COMMONKIT__INCLUDED_
