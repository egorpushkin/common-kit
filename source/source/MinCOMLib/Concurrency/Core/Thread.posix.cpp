#include "Common/Common.h"

#include "Thread.h"

namespace MinCOM
{

    void * Thread::_ThreadWorkingRoutine(void* param)
	{
		// Acquire object wrapping the thread.
		Thread *thread = static_cast< Thread* >(param);
		if ( !thread )
			return NULL;

		// Increment internal thread's counter to ensure that the thread will 
		// be still alive after job is done.
		static_cast< CommonImpl< IThread >* >(thread)->IncrementReference();

		try
		{
			// Execute thread
			_ThreadExecutor(thread);
		} 
		catch( ... )
		{
		}

		// Decrement internal counter.
		static_cast< CommonImpl< IThread >* >(thread)->DecrementReference();

		return NULL;
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
		, thread_()
        , running_(false)
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
		}

		// Start thread
		pthread_attr_t threadAttributes;
		int code = pthread_attr_init(&threadAttributes);
		if ( 0 != code )
			return _E_FAIL;
		code = pthread_attr_setdetachstate(&threadAttributes, PTHREAD_CREATE_JOINABLE);
		if ( 0 != code )
			return _E_FAIL;
		code = pthread_create(&thread_, &threadAttributes, Thread::_ThreadWorkingRoutine, this);
		if ( 0 != code )
			return _E_FAIL;
		pthread_attr_destroy(&threadAttributes);
		if ( 0 != code )
			return _E_FAIL;        
        
        running_ = true;
        
		return _S_OK;
	}

	result Thread::Join()
	{
		return Wait(_INFINITE);
	}

	// ISynchro section
	result Thread::Wait(unsigned long /* milliseconds *//* = _INFINITE */)
	{
		// This routine must not (!) block execution because it performs blocking itself,
		// does not modify internal object's state and relies on it's internal representation 
		// (thread handle).

		int code = pthread_join(thread_, NULL);        
        return ( code == 0 ) ? ( _S_OK ) : ( _E_FAIL );
	}
    
    result Thread::Close()
    {
        return _E_NOTIMPL;
    }

	// Internal tools
	//////////////////////////////////////////////////////////////////////////

	bool Thread::IsStarted()
	{
		return running_;
	}

	IRunnablePtr Thread::GetContext()
	{
		return context_;
	}

	void Thread::Finalize()
	{
        running_ = false;
	}

}
