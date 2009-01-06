#ifndef THREAD_H__MINCOM__CORELIB__INCLUDED_
#define THREAD_H__MINCOM__CORELIB__INCLUDED_

namespace MinCOM
{

	class Thread 
		: public CommonImpl< IThread >
		, public CommonImpl< ISynchro >
	{
		
		friend unsigned long mc_stdcall ThreadWorkingRoutine(void*);

	public:

		Thread();
		virtual ~Thread();

		// ICommon section
		DECLARE_INTERFACE_MAP()		

		// IThread section
		virtual result SetContext(IAgentRef context, DispParamsRef params = NULL);

		virtual result SetPriority(int priority);

		virtual result Start();

		virtual result Suspend();

		virtual result Resume();

		virtual result Terminate();		

		virtual result GetExitCode();

		virtual result Join();

		// ISynchro section
		virtual result Wait(unsigned long milliseconds = INFINITE);

		virtual result Signal();

		virtual result Reset();

	private:

		// ThreadWorkingRoutine tools
		void Finilize();

	private:

		IAgentPtr context_;

		DispParamsPtr params_;

		int priority_;

		class ThreadImpl_;	

		typedef Loki::SmartPtr< ThreadImpl_ > ThreadImplPtr_;

		ThreadImplPtr_ threadImpl_;

		IMutexPtr lock_;

		bool started_;

		result exitCode_;

	};

}

#endif // !THREAD_H__MINCOM__CORELIB__INCLUDED_
