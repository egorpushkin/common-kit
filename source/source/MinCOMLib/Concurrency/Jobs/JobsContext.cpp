#include "Common/Common.h"

#include "JobsContext.h"

namespace MinCOM
{

	JobsContext::JobsContext(IJobsQueueRef jobsQueue, IEventRef newJobSignal)
		: CommonImpl< IRunnable >()
		, jobsQueue_(jobsQueue)
		, newJobSignal_(newJobSignal)
	{
	}

	// IAgent section
	result JobsContext::Run()
	{		
		if ( !jobsQueue_ || !newJobSignal_ )
			return _E_FAIL;			

		bool forever = true;
		while ( forever )
		{
			if ( Error::IsFailed(newJobSignal_->Wait()) )
				return _E_FAIL;

			newJobSignal_->Reset();

			// Process pending jobs
			if ( Error::IsFailed(DoJobs(jobsQueue_)) )
			{
				// Stop execution if internal processing routine has failed 
				break;
			}

			forever = jobsQueue_->ContinueExecution();
		}

		return _S_OK;
	}

	mc::result JobsContext::DoJobs(IJobsQueueRef jobsQueue)
	{
		while ( Error::IsSucceeded(jobsQueue->Execute()) );
		return _S_OK;
	}

}
