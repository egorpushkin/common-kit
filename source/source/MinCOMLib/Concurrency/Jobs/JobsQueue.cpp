#include "Common/Common.h"

#include "JobsQueue.h"
#include "JobsContext.h"

// Required for std::numeric_limits< T >::max() to work.
#undef max

namespace MinCOM
{

	JobsQueue::JobsQueue()
		: mc::CommonImpl< IJobsQueue >()
		, mc::CommonImpl< ISynchro >()
		, workingThread_()
		, jobs_()
		, continueExecution_(false)
	{
	}
		
	JobsQueue::~JobsQueue()
	{
		Stop();
	}

	// IJobsQueue section
	result JobsQueue::Run()
	{
		CoreMutexLock lock(CommonImpl< ISynchro >::GetLock());

		if ( workingThread_ )
			return mc::_E_ALREADYINIT;

		// Initially flush signals
		jobsCounter_ = Library::Semaphore(0, std::numeric_limits< long >::max());

		// Initialize termination criterion
		continueExecution_ = true;

		// Configure and start jobs' processing thread
		workingThread_ = Library::Thread();
		workingThread_->SetContext(
			Class< JobsContext >::Create(CommonImpl< IJobsQueue >::GetSelf(), jobsCounter_) );
		workingThread_->Start();

		return mc::_S_OK;
	}

	result JobsQueue::Stop()
	{
		CoreMutexLock lock(CommonImpl< ISynchro >::GetLock());

		if ( !workingThread_ )
			return mc::_E_NOTINIT;

		// Stop internal thread
		continueExecution_ = false;

		// Signal on fake job 
		if ( jobsCounter_ )
			jobsCounter_->Release();

		// Waiting for thread termination
		workingThread_->Join();

		// Destroy thread of execution 
		workingThread_ = NULL;

		return mc::_S_OK;
	}

	result JobsQueue::Push(IRunnableRef job)
	{
		CoreMutexLock lock(CommonImpl< ISynchro >::GetLock());

		// Check arguments
		if ( !job )
			return mc::_E_INVALIDARG;

		// Register new job
		jobs_.push(job);

		// Notify processing thread
		jobsCounter_->Release(1);
	
		return mc::_S_OK;
	}

	result JobsQueue::Execute()
	{	
		// This call must be non-blocking except element extraction performed by Pop method.

		// Extract next job.
		IRunnablePtr job = Pop();
		if ( !job )
			return mc::_E_FAIL;
		
		// Do the job.
		job->Run();

		// Return success regardless of job's return code.
		return mc::_S_OK;
	}

	bool JobsQueue::ContinueExecution()
	{
		// Should not be blocking. 
		// TODO: Interlocked routine should be used to operate with this flag.
		return continueExecution_;
	}

	// ISynchro section
	result JobsQueue::Wait(unsigned long /* delay *//* = _INFINITE */)
	{
		// Do not block this method to prevent self blocking.

		// Wait for context thread termination here.
		return workingThread_->Join();
	}

	result JobsQueue::Close()
	{
		return _E_NOTIMPL;
	}

	// Internal tools
	IRunnablePtr JobsQueue::Pop()
	{
		CoreMutexLock lock(CommonImpl< ISynchro >::GetLock());

		// Check whether it is still required to process jobs.
		if ( !continueExecution_ )
			return NULL;

		// Check whether there is a job to be processed.
		if ( jobs_.size() == 0 )
			return NULL;

		// Extract and return the oldest one job (from the front of the queue).
		IRunnablePtr job = jobs_.front();
		jobs_.pop();

		return job;
	}

}
