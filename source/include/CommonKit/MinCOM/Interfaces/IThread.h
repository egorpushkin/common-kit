#ifndef ITHREAD_H__MINCOM__COMMONKIT__INCLUDED_
#define ITHREAD_H__MINCOM__COMMONKIT__INCLUDED_

namespace MinCOM
{

	interface IThread : public ICommon
	{

		virtual result SetContext(IAgentRef context, DispParamsRef params = NULL) = 0;

		virtual result SetPriority(int priority) = 0;

		virtual result Start() = 0;

		virtual result Suspend() = 0;

		virtual result Resume() = 0;

		virtual result Terminate() = 0;		

		virtual result GetExitCode() = 0;

		virtual result Join() = 0;

	};

	typedef ComPtr< IThread > IThreadPtr;
	typedef const IThreadPtr& IThreadRef;

	// {c76d8df5-1dab-4375-b1f2-f532b4300185} 
	MC_DEFINE_GUID(IID_IThread, 
	0xc76d8df5, 0x1dab, 0x4375, 0xb1, 0xf2, 0xf5, 0x32, 0xb4, 0x30, 0x01, 0x85);

	// {ba76df9f-9532-475e-a3b0-01b00e18753e} 
	MC_DEFINE_GUID(CLSID_Thread, 
	0xba76df9f, 0x9532, 0x475e, 0xa3, 0xb0, 0x01, 0xb0, 0x0e, 0x18, 0x75, 0x3e);

	// Thread events
	typedef enum tagThreadEvents
	{
	
		AGENTID_MAINCTXCALL = 0xff010A01

	} ThreadEvents;

	// Thread priority
	typedef enum tagThreadPriority
	{

		MODE_BACKGROUND_BEGIN = 0x00010000,		

		MODE_BACKGROUND_END = 0x00020000,		

		PRIORITY_ABOVE_NORMAL = 1,

		PRIORITY_BELOW_NORMAL = -1,

		PRIORITY_HIGHEST = 2,

		PRIORITY_IDLE = -15,

		PRIORITY_LOWEST = -2,

		PRIORITY_NORMAL = 0,

		PRIORITY_TIME_CRITICAL = 15

	} ThreadPriority;

	IThreadPtr InstantiateThread();

}

#endif // !ITHREAD_H__MINCOM__COMMONKIT__INCLUDED_
