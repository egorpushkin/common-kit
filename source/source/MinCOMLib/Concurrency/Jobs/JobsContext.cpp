#include "Common/Common.h"

#include "JobsContext.h"

namespace MinCOM
{

	JobsContext::JobsContext(IJobsQueueRef jobsQueue, ISemaphoreRef jobsCounter)
		: CommonImpl< IRunnable >()
		, jobsQueue_(jobsQueue)
		, jobsCounter_(jobsCounter)
	{
	}

	// IRunnable section
	result JobsContext::Run()
	{		
		if ( !jobsQueue_ || !jobsCounter_ )
			return _E_FAIL;			

		bool forever = true;
		while ( forever )
		{
			// Wait until any job arrives.
			if ( Error::IsFailed(jobsCounter_->Wait()) )
				return _E_FAIL;

			// Acquire jobs queue.
			IJobsQueuePtr jobsQueue(jobsQueue_);
			if ( !jobsQueue )
				return _E_FAIL;
	
			// Execute a job.
			jobsQueue->Execute();			

			// Check whether additional processing is required.
			forever = jobsQueue->ContinueExecution();
		}

		return _S_OK;
	}

}
