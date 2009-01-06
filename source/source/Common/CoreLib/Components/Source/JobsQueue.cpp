#include "Common/Common.h"

#include "CommonKit/Components.h"

#include "CommonKit/Project.h"

#include "JobsQueue.h"

#include "JobsContext.h"

namespace Components
{

	JobsQueue::JobsQueue()
		: mc::CommonImpl< IJobsQueue >()
		, mc::CommonImpl< mc::ISynchro >()
		, mc::ItemImpl()
		, lockStartStop_(mc::InstantiateMutex())
		, lockQueue_(mc::InstantiateMutex())
		, workingThread_()
		, newJobSignal_(mc::InstantiateEvent())
		, jobs_()
		, continueExecution_(false)
	{
	}
		
	JobsQueue::~JobsQueue()
	{
		Stop();
	}

	// ICommon section
	BEGIN_INTERFACE_MAP(JobsQueue)
		COMMON(IJobsQueue)
		INTERFACE_(IJobsQueue, IID_IJobsQueue)
		INTERFACE_(mc::ISynchro, mc::IID_ISynchro)
		IMPL(mc::ItemImpl)
	END_INTERFACE_MAP()		

	// IJobsQueue section
	mc::result JobsQueue::Start()
	{
		mc::MutexLock lock(lockStartStop_);

		if ( workingThread_ )
			return mc::_E_FAIL;

		// Initially flush signals
		newJobSignal_->Reset();

		// Initialize termination criterion
		continueExecution_ = true;

		// Configure and execute jobs' processing thread
		workingThread_ = mc::InstantiateThread();
		workingThread_->SetPriority(mc::PRIORITY_LOWEST);
		workingThread_->SetContext(
			mc::InstantiateAgent< JobsContext >(),
			mc::CreateParams(mc::ItemImpl::GetLocal(), newJobSignal_)
		);
		workingThread_->Start();

		return mc::_S_OK;
	}

	mc::result JobsQueue::Stop()
	{
		mc::MutexLock lock(lockStartStop_);

		if ( !workingThread_ )
			return mc::_E_FAIL;

		// Stop internal thread
		continueExecution_ = false;

		// Signal on fake job 
		newJobSignal_->Signal();

		// Waiting for thread termination
		mc::ISynchroPtr threadSynchro(workingThread_, mc::IID_ISynchro);
		if ( !threadSynchro )
		{
			workingThread_ = NULL;
			return mc::_S_FALSE;
		}
				
		threadSynchro->Wait();

		// Destroy thread of execution 
		threadSynchro = NULL;
		workingThread_ = NULL;

		return mc::_S_OK;
	}

	mc::result JobsQueue::Push(mc::IAgentRef jobExec, mc::DispParamsRef params /* = NULL */)
	{
		mc::MutexLock lock(lockQueue_);

		// Check arguments
		if ( !jobExec )
			return mc::_E_INVALIDARG;

		// Construct job
		JobPtr_ job(new Job_);
		job->jobExecutor_ = jobExec;
		job->params_ = params;

		// Add new job
		jobs_.push(job);

		// Notify processing thread
		newJobSignal_->Signal();
	
		return mc::_S_OK;
	}

	mc::result JobsQueue::Execute()
	{	
		// This call must be non-blocking except element extraction performed by Pop method.

		// Extract next job
		JobPtr_ job = Pop();
		if ( !job )
			return mc::_E_FAIL;
		
		// Do! job
		job->jobExecutor_->Invoke(AGENTID_MAINJOBCALL, job->params_);

		// Return success regardless of job's return code
		return mc::_S_OK;
	}

	bool JobsQueue::ContinueExecution()
	{
		return continueExecution_;
	}

	// ISynchro section
	mc::result JobsQueue::Wait(unsigned long milliseconds /* = INFINITE */)
	{
		// Do not synchronize this method with other to prevent self blocking.

		// Waiting for context thread termination here
		mc::ISynchroPtr threadSynch(workingThread_, mc::IID_ISynchro);

		if ( !threadSynch )
			return mc::_E_FAIL;

		return threadSynch->Wait(milliseconds);
	}

	mc::result JobsQueue::Signal()
	{
		return mc::_E_NOTIMPL;
	}

	mc::result JobsQueue::Reset()
	{		
		return mc::_E_NOTIMPL;
	}

	// Private tools
	JobsQueue::JobPtr_ JobsQueue::Pop()
	{
		mc::MutexLock lock(lockQueue_);

		if ( jobs_.size() == 0 )
			return NULL;

		JobPtr_ job = jobs_.front();

		jobs_.pop();

		return job;
	}

	// External tools
	IJobsQueuePtr InstantiateJobsQueue()
	{
		return IJobsQueuePtr(mc::ObjectCreator< JobsQueue >(), IID_IJobsQueue);
	}

}
