#ifndef THREAD_H__MINCOMLIB__INCLUDED_
#define THREAD_H__MINCOMLIB__INCLUDED_

namespace MinCOM
{

	class Thread 
		: public CommonImpl< IThread >
		, public CommonImpl< ISynchro >
	{
		
		// friend unsigned int mc_stdcall _ThreadWorkingRoutine(void*);

		/**
		 * Thread entry point.
		 */
		static unsigned int mc_stdcall _ThreadWorkingRoutine(void*);

		/**
		 * Executes context of particular thread.
		 */
		static unsigned int _ThreadExecutor(Thread * thread);

	public:

		Thread();
		virtual ~Thread();

		// IThread section
		virtual result SetContext(IRunnableRef context);

		virtual result Start();

		virtual result Join();

		// ISynchro section
		virtual result Wait(unsigned long milliseconds = _INFINITE);

	protected:

		bool IsStarted();

		/**
		 * Tool to provide working routine with thread context.
		 */ 
		IRunnablePtr GetContext();

		/**
		 * Thread working routine calls this method to indicate that
		 * the job is done. 
		 * This tool should be designed to be called from ~Thread as well.
		 */ 
		void Finalize();

	private:

#ifdef WIN32
		/** Handle for win32 environments. */
		HANDLE thread_;
#elif POSIX
		/** Handle for posix environments. */
		
#endif

		/** Thread context. */
		IRunnablePtr context_;

	};

}

#endif // !THREAD_H__MINCOMLIB__INCLUDED_
