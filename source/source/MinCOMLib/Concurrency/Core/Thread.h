#ifndef THREAD_H__MINCOMLIB__INCLUDED_
#define THREAD_H__MINCOMLIB__INCLUDED_

namespace MinCOM
{

	class Thread 
		: public CommonImpl< IThread >
		, public CommonImpl< ISynchro >
	{   
		
		/**
		 * Thread entry point.
		 */
#if defined(WIN32)
        static unsigned int mc_stdcall _ThreadWorkingRoutine(void*);
#elif defined(POSIX)
        static void * _ThreadWorkingRoutine(void*);
#endif
        
		/**
		 * Executes context of particular thread.
		 */
		static unsigned int _ThreadExecutor(Thread * thread);

	public:

		typedef CommonImpl< IThread > ClassRoot_;     
        
		Thread();
		virtual ~Thread();

		// IThread section
		virtual result SetContext(IRunnableRef context);

		virtual result Start();

		virtual result Join();

		// ISynchro section
		virtual result Wait(unsigned long milliseconds = _INFINITE);

		virtual result Close();

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

#if defined(WIN32)
		/** Handle for win32 environments. */
		HANDLE thread_;
#elif defined(POSIX)
		/** Handle for posix environments. */
		pthread_t thread_;
        /** Indicates whether thread is still running. */
        bool running_;
#endif

		/** Thread context. */
		// TODO: Reference to context should be weak.
		IRunnablePtr context_;

	};

}

#endif // !THREAD_H__MINCOMLIB__INCLUDED_
