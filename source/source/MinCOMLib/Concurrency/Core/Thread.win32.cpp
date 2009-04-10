#include "Common/Common.h"

#include "Thread.h"

#include "Platforms/win32/Concurrent.win32.h"

namespace MinCOM
{

	unsigned int __stdcall Thread::_ThreadWorkingRoutine(void* param)
	{
		// Acquire object wrapping the thread.
		Thread *thread = static_cast< Thread* >(param);
		if ( !thread )
			return 1;

		// Increment internal thread's counter to ensure that the thread will 
		// be still alive after job is done.
		static_cast< CommonImpl< IThread >* >(thread)->IncrementReference();

		int code = 0;
		try
		{
			// Execute thread
			code = _ThreadExecutor(thread);
		} 
		catch( ... )
		{
		}

		// Decrement internal counter.
		static_cast< CommonImpl< IThread >* >(thread)->DecrementReference();

		return code;
	}

	unsigned int Thread::_ThreadExecutor(Thread * thread)
	{
		if ( !thread )
			return 1;

		// Get context for execution.
		IRunnablePtr context = thread->GetContext();
		if ( !context )
		{
			thread->Finalize();
			return 1;
		}

		// Run context.
		context->Run();

		// Notify thread object on completion.
		thread->Finalize();

		return 0;
	}

	Thread::Thread()
		: CommonImpl< IThread >()
		, CommonImpl< ISynchro >()
		, thread_(NULL)
		, context_()
	{
	}

	Thread::~Thread()
	{	
		Finalize();
	}

	// IThread section
	result Thread::SetContext(IRunnableRef context)
	{
		if ( IsStarted() )
		{
			// Impossible to change context of execution while the thread 
			// is running.
			return _E_FAIL;
		}
		context_ = context;
		return _S_OK;
	}

	result Thread::Start()
	{
		if ( !context_ )
			return _E_NOTINIT;

		if ( IsStarted() )
		{
			// Impossible to restart the thread in such a way.
			return _E_ALREADYINIT;
		}
		else
		{
			// Close previous handle before restarting.
			if ( thread_ )
				::CloseHandle(thread_);
		}

		// Start thread
		unsigned int threadId = 0;
		thread_ = (HANDLE)_beginthreadex(NULL, 0, _ThreadWorkingRoutine, this, 0, &threadId); 
		if ( !thread_ )
		{
			// Error creating thread
			return _E_FAIL;
		}

		return _S_OK;
	}

	result Thread::Join()
	{
		return Wait(_INFINITE);
	}

	// ISynchro section
	result Thread::Wait(unsigned long milliseconds /* = _INFINITE */)
	{
		// This routine must not (!) block execution because it performs blocking itself,
		// does not modify internal object's state and relies on it's internal representation 
		// (thread handle).

		return ConcurrentWin32::Wait(thread_, milliseconds);
	}

	result Thread::Close()
	{
		return _E_NOTIMPL;
	}

	// Internal tools
	//////////////////////////////////////////////////////////////////////////

	bool Thread::IsStarted()
	{
		return ( ( thread_ ) && ( WAIT_TIMEOUT == ::WaitForSingleObject(thread_, 0) ) );
	}

	IRunnablePtr Thread::GetContext()
	{
		return context_;
	}

	void Thread::Finalize()
	{
		if ( !thread_ )
			return;
		::CloseHandle(thread_);
		thread_ = NULL;
	}

}
