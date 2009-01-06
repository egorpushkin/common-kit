#ifndef DCONTAINEREVENTS_H__CONTAINER__COMMONKIT__INCLUDED_
#define DCONTAINEREVENTS_H__CONTAINER__COMMONKIT__INCLUDED_

namespace Container
{

	interface DContainerEvents : public mc::ICommon
	{

		virtual mc::result OnAddElement(void* const pData, bool* pCancel) = 0;
		virtual mc::result OnDeleteElement(void* const pData, int index, bool* pCancel) = 0;

	};

	typedef mc::ComPtr< DContainerEvents > DContainerEventsPtr;

	// {24c4b8da-0375-4346-9445-d64fbaa2ddc6} 
	MC_DEFINE_GUID(DIID_DContainerEvents, 
	0x24c4b8da, 0x0375, 0x4346, 0x94, 0x45, 0xd6, 0x4f, 0xba, 0xa2, 0xdd, 0xc6);

	enum
	{
		AGENTID_ADDELEMENT = 1,
		AGENTID_DELETEELEMENT
	};

}

#endif // !DCONTAINEREVENTS_H__CONTAINER__COMMONKIT__INCLUDED_
