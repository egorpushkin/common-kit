#ifndef IAREA_H__AREASKIT__INCLUDED_
#define IAREA_H__AREASKIT__INCLUDED_

namespace Areas
{

	interface IArea : public mc::ICommon
	{

		virtual void SetName(const mc::StringA& name) = 0;

		virtual mc::StringA GetName() = 0;

	};

	typedef mc::ComPtr< IArea > IAreaPtr;
	typedef const IAreaPtr& IAreaRef;

	// {6540bd20-432e-4461-bb27-004011607639} 
	MC_DEFINE_GUID(IID_IArea, 
	0x6540bd20, 0x432e, 0x4461, 0xbb, 0x27, 0x00, 0x40, 0x11, 0x60, 0x76, 0x39);

	enum
	{
		AGENTID_ADDINGPOINT = AGENTID_LAST_PT_EVENT + 1,
		AGENTID_POINTADDED,
		AGENTID_DELETINGPOINT,
		AGENTID_POINTDELETED,
		AGENTID_AREANAMECHANGED,
		AGENTID_LAST_AREA_EVENT
	};

}

#endif // !IAREA_H__AREASKIT__INCLUDED_
