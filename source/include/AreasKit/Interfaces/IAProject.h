#ifndef IAPROJECT_H__AREASKIT__INCLUDED_
#define IAPROJECT_H__AREASKIT__INCLUDED_

namespace Areas
{

	interface IAProject : public mc::ICommon
	{

		virtual IMsImagePtr GetImage() = 0;

	};

	typedef mc::ComPtr< IAProject > IAProjectPtr;
	typedef const IAProjectPtr& IAProjectRef;

	// {157bf9d8-ab09-4d8e-80a3-44e96fd3b063} 
	MC_DEFINE_GUID(IID_IAProject, 
	0x157bf9d8, 0xab09, 0x4d8e, 0x80, 0xa3, 0x44, 0xe9, 0x6f, 0xd3, 0xb0, 0x63);

	enum
	{
		AGENTID_ADDINGAREA = AGENTID_LAST_AREA_EVENT + 1,
		AGENTID_AREAADDED,
		AGENTID_DELETINGAREA,
		AGENTID_AREADELETED,
		AGENTID_LAST_PROJECT_EVENT
	};

}

#endif // !IAPROJECT_H__AREASKIT__INCLUDED_
