#ifndef ICOMPONENTSMANAGER_H__COMPONENTS__COMMONKIT__INCLUDED_
#define ICOMPONENTSMANAGER_H__COMPONENTS__COMMONKIT__INCLUDED_

namespace Components
{

	interface IComponentsManager : public mc::ICommon
	{

		virtual mc::ICommonPtr InstantiateCommon(mc::RefClsid clsid) = 0;
		
		virtual mc::ICommonPtr InstantiateCommon(mc::RefIid libIid, mc::RefClsid clsid) = 0;

		virtual mc::ICommonPtr InstantiateByTypeIid(mc::RefIid typeIid, mc::RefClsid clsid) = 0;

		virtual mc::result UnregisterComponent(mc::RefIid iid) = 0;		

		virtual IJobsQueuePtr GetJobs() = 0;

	};

	typedef mc::ComPtr< IComponentsManager > IComponentsManagerPtr;
	typedef const IComponentsManagerPtr& IComponentsManagerRef;

	typedef mc::ComPtr< IComponentsManager, false > IComponentsManagerWeak;

	// {bc8a1584-130b-4ad2-ae40-93edd3a2177f} 
	MC_DEFINE_GUID(IID_IComponentsManager, 
	0xbc8a1584, 0x130b, 0x4ad2, 0xae, 0x40, 0x93, 0xed, 0xd3, 0xa2, 0x17, 0x7f);

	// Manager events
	enum
	{
		AGENTID_ADDINGINSTANCE = 0xff010001,
		AGENTID_INSTANCEADDED,
		AGENTID_DELETINGINSTANCE,
		AGENTID_INSTANCEDELETED,
		AGENTID_LAST_CM_EVENT
	};

}

#endif // !ICOMPONENTSMANAGER_H__COMPONENTS__COMMONKIT__INCLUDED_
