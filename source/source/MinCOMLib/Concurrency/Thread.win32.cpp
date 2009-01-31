#include "Common/Common.h"

#include "Thread.h"

#include "CommonKit/Platform.h"

namespace MinCOM
{

	unsigned long __stdcall ThreadWorkingRoutine(void* param);
	
	class Thread::ThreadImpl_
	{
	public:

		ThreadImpl_()
			: thread_(NULL)
		{
		}

		~ThreadImpl_()
		{
			Finilize();
		}

		result SetPriority(int priority)
		{
			if ( !thread_ )
				return _E_FAIL;

			if ( !::SetThreadPriority(thread_, priority) )
				return _S_FALSE;

			return _S_OK;
		}

		result Start(Thread* pThread)
		{
			if ( thread_ )
			{
				// Handle hasn't been released after previous operation
				return _E_FAIL;
			}

			unsigned long threadId = 0;
			thread_ = ::CreateThread(NULL, 0, ThreadWorkingRoutine, pThread, CREATE_SUSPENDED, &threadId);
			if ( !thread_ )
			{
				// Error creating thread
				return _E_FAIL;
			}

			if ( IsFailed(SetPriority(pThread->priority_)) )
			{
				Finilize();
				return _E_FAIL;
			}

			Resume();

			return _S_OK;
		}

		result Suspend()
		{
			if ( !thread_ )
				return _E_FAIL;

			::SuspendThread(thread_);

			return _S_OK;
		}

		result Resume()
		{
			if ( !thread_ )
				return _E_FAIL;

			::ResumeThread(thread_);

			return _S_OK;
		}

		result Terminate()
		{	
			if ( !thread_ )
				return _E_FAIL;

			::TerminateThread(thread_, 0x0);

			Finilize();

			return _S_OK;
		}

		void Finilize()
		{
			if ( !thread_ )  
				return;

			::CloseHandle(thread_);

			thread_ = NULL;
		}

		result Wait(unsigned long milliseconds = INFINITE)
		{		
			unsigned long waitResult = ::WaitForSingleObject(thread_, milliseconds);

			if ( waitResult == WAIT_ABANDONED || waitResult == WAIT_FAILED )
				return _E_FAIL;

			if ( waitResult == WAIT_TIMEOUT )
				return _S_FALSE;

			// waitResult == WAIT_OBJECT_0
			return _S_OK;
		}		

	private:

		HANDLE thread_;

	};

	unsigned long __stdcall ThreadWorkingRoutine(void* param)
	{
		try
		{
		
			Thread* pThread = static_cast< Thread* >(param);
			if ( !pThread )
				return 1;

			IAgentPtr context = pThread->context_;
			if ( !context )
			{
				pThread->Finilize();
				return 1;
			}

			pThread->exitCode_ = context->Invoke(AGENTID_MAINCTXCALL, pThread->params_);

			pThread->Finilize();

		} 
		catch( ... )
		{
		}

		return 0;
	}

	Thread::Thread()
		: CommonImpl< IThread >()
		, CommonImpl< ISynchro >()
		, context_()
		, params_()
		, priority_(0)
		, threadImpl_(new ThreadImpl_)
		, lock_(InstantiateMutex())
		, started_(false)
		, exitCode_(_S_OK)
	{
	}

	Thread::~Thread()
	{	
		MutexLock lock(lock_);

		if ( started_ )
			Terminate();
	}

	// ICommon section
	BEGIN_INTERFACE_MAP(Thread)
		COMMON(IThread)
		INTERFACE_(IThread, IID_IThread)
		INTERFACE_(ISynchro, IID_ISynchro)
	END_INTERFACE_MAP()		

	result Thread::SetContext(IAgentRef context, DispParamsRef params /* = NULL */)
	{
		MutexLock lock(lock_);

		if ( started_ )
			return _E_FAIL;

		context_ = context;
		params_ = params;

		return _S_OK;
	}

	result Thread::SetPriority(int priority)
	{
		MutexLock lock(lock_);

		priority_ = priority;
		
		return threadImpl_->SetPriority(priority_);
	}	

	result Thread::Start()
	{
		MutexLock lock(lock_);

		if ( started_ )
			return _E_FAIL;

		if ( !context_ )
			return _E_FAIL;

		exitCode_ = _S_OK;

		result code = threadImpl_->Start(this);
		
		if ( IsSucceeded(code) )
			started_ = true;

		return code;
	}

	result Thread::Suspend()
	{
		MutexLock lock(lock_);

		if ( !started_ )
			return _E_FAIL;

		return threadImpl_->Suspend();
	}

	result Thread::Resume()
	{
		MutexLock lock(lock_);

		if ( !started_ )
			return _E_FAIL;

		return threadImpl_->Resume();
	}

	result Thread::Terminate()
	{
		MutexLock lock(lock_);

		if ( !started_ )
			return _E_FAIL;

		result code = threadImpl_->Terminate();

		exitCode_ = _E_FAIL;

		if ( IsSucceeded(code) )
			started_ = false;

		return code;
	}

	result Thread::GetExitCode()
	{
		MutexLock lock(lock_);

		return exitCode_;
	}

	result Thread::Join()
	{
		return Wait();
	}

	// ISynchro section
	result Thread::Wait(unsigned long milliseconds /* = INFINITE */)
	{
		// This function must not (!) block execution because it performs blocking itself
		// and does not modify internal object's state only relying on it's internal representation 
		// (thread handle storage).

		return threadImpl_->Wait(milliseconds);
	}

	result Thread::Signal()
	{
		return _E_NOTIMPL;
	}

	result Thread::Reset()
	{		
		return _E_NOTIMPL;
	}

	// ThreadWorkingRoutine tools
	void Thread::Finilize()
	{
		MutexLock lock(lock_);

		started_ = false;

		threadImpl_->Finilize();
	}

}