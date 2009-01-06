#ifndef ICONTAINEREVENTS_H__PROJECT__COMMONKIT__INCLUDED_
#define ICONTAINEREVENTS_H__PROJECT__COMMONKIT__INCLUDED_

namespace Project
{

	interface IContainerEvents : public mc::ICommon
	{

		virtual void SetOnBeforeAdd(mc::DispId id) = 0;
		
		virtual void SetOnAfterAdd(mc::DispId id) = 0;

		virtual void SetOnBeforeDelete(mc::DispId id) = 0;

		virtual void SetOnAfterDelete(mc::DispId id) = 0;

		virtual mc::DispId GetOnBeforeAdd() = 0;

		virtual mc::DispId GetOnAfterAdd() = 0;

		virtual mc::DispId GetOnBeforeDelete() = 0;

		virtual mc::DispId GetOnAfterDelete() = 0;

	};

	typedef mc::ComPtr< IContainerEvents > IContainerEventsPtr;
	typedef const IContainerEventsPtr& IContainerEventsRef;

	// {6c774126-bd8e-403d-94f4-2e1643c54423} 
	MC_DEFINE_GUID(IID_IContainerEvents, 
	0x6c774126, 0xbd8e, 0x403d, 0x94, 0xf4, 0x2e, 0x16, 0x43, 0xc5, 0x44, 0x23);

	typedef enum tagContainerEvents
	{

		AGENTID_ADDINGITEM = 0x0100,
		AGENTID_ITEMADDED,
		AGENTID_DELETINGITEM,
		AGENTID_ITEMDELETED,
		AGENTID_BEFORECLEAR,
		AGENTID_CLEARED,
		AGENTID_LAST_CONTCORE_EVENT

	} ContainerEvents;

}

#endif // !ICONTAINEREVENTS_H__PROJECT__COMMONKIT__INCLUDED_
