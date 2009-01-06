#ifndef ISELECTORCONTROL_H__AREASSELECTOR__INCLUDED_
#define ISELECTORCONTROL_H__AREASSELECTOR__INCLUDED_

namespace AreasSelector
{

	interface ISelectorControl : public mc::ICommon
	{

		virtual mc::result SetProject(Areas::IAProjectRef project) = 0;

		virtual Areas::IAProjectPtr GetProject() = 0;

	};

	typedef mc::ComPtr< ISelectorControl > ISelectorControlPtr;
	typedef const ISelectorControlPtr& ISelectorControlRef;

	// {290fe4a2-6a86-4bd1-b5b5-78fde12a5a5a} 
	MC_DEFINE_GUID(IID_ISelectorControl, 
	0x290fe4a2, 0x6a86, 0x4bd1, 0xb5, 0xb5, 0x78, 0xfd, 0xe1, 0x2a, 0x5a, 0x5a);

	typedef enum tagSelectorEvents
	{

		// Events
		AGENTID_PROJECTCHANGED = 0x00020001,
		// Commands
		AGENTID_DISPLAYPROPERTIES = 0x00020002,
		AGENTID_LAST_SELECTOR_EVENT

	} SelectorEvents;

}

#endif // !ISELECTORCONTROL_H__AREASSELECTOR__INCLUDED_
