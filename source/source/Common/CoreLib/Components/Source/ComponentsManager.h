#ifndef COMPONENTSMANAGER_H__COMPONENTS__COMMONKIT__INCLUDED_
#define COMPONENTSMANAGER_H__COMPONENTS__COMMONKIT__INCLUDED_

namespace Components
{

	class ComponentsManager 
		: public mc::CommonImpl< IComponentsManager >		
		, public mc::AgentImpl
		, public mc::ItemImpl
		, public mc::CookiesHelper
	{
	public:

		ComponentsManager();
		virtual ~ComponentsManager();

		// ICommon section
		DECLARE_INTERFACE_MAP()		

		// IComponentsManager section
		virtual mc::ICommonPtr InstantiateCommon(mc::RefClsid clsid);

		virtual mc::ICommonPtr InstantiateCommon(mc::RefIid libIid, mc::RefClsid clsid);

		virtual mc::ICommonPtr InstantiateByTypeIid(mc::RefIid typeIid, mc::RefClsid clsid);

		virtual mc::result UnregisterComponent(mc::RefIid iid);	

		virtual IJobsQueuePtr GetJobs();

		// IAgent section
		virtual mc::result Invoke(mc::DispId idMember, mc::DispParamsRef dispParams, mc::IVariantWrapperRef result, mc::RefIid iid);

	private:

		// Private tools
		virtual mc::ICommonPtr InstantiateCommon(mc::RefClsid clsid, mc::RefIid iid, ComponentChecker::Method_ method, mc::RefIid typeIid = TYPEID_General);

		mc::ICommonPtr TryConstructLocally(mc::RefClsid clsid, mc::RefIid iid, ComponentChecker::Method_ method);

		mc::ICommonPtr TryConstructGlobally(mc::RefClsid clsid, mc::RefIid iid, ComponentChecker::Method_ method, mc::RefIid typeIid = TYPEID_General);

		IComponentInstancePtr FindInstance(mc::RefIid iid);

	private:

		mc::IMutexPtr lock_;

		IJobsQueuePtr jobs_;

		Container::ICommonsPtr components_;

	};

	// Creator
	class ComponentsManagerCreator
		: public mc::CommonHolder< ComponentsManager >
	{

		typedef mc::CommonHolder< ComponentsManager > CommonHolder_;

	public:

		ComponentsManagerCreator();
		~ComponentsManagerCreator();

	};

	// Holder
	typedef Loki::SingletonHolder
	<
		ComponentsManagerCreator
	> 
	ComponentsManagerHolder;

	// External tools
	IComponentsManagerPtr GetComponentsManager();

}

#endif // !COMPONENTSMANAGER_H__COMPONENTS__COMMONKIT__INCLUDED_