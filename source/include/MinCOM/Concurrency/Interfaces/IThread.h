#ifndef ITHREAD_H__MINCOM__COMMONKIT__INCLUDED_
#define ITHREAD_H__MINCOM__COMMONKIT__INCLUDED_

namespace MinCOM
{

	/**
	 * 
	 */
	interface IThread : public ICommon
	{

		virtual result SetContext(IRunnableRef context) = 0;

		virtual result SetPriority(int priority) = 0;

		virtual result Start() = 0;

		virtual result Suspend() = 0;

		virtual result Resume() = 0;

		virtual result Terminate() = 0;		

		virtual long GetExitCode() = 0;

		virtual result Join() = 0;

	};

	typedef ComPtr< IThread > IThreadPtr;
	typedef const IThreadPtr& IThreadRef;

	/*
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
	*/

	IThreadPtr InstantiateThread();

}

#endif // !ITHREAD_H__MINCOM__COMMONKIT__INCLUDED_
