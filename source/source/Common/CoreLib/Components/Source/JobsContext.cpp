#include "Common/Common.h"

#include "CommonKit/Components.h"

#include "JobsContext.h"

namespace Components
{

	JobsContext::JobsContext()
		: mc::AgentImpl()
	{
	}

	JobsContext::~JobsContext()
	{
	}

	// IAgent section
	mc::result JobsContext::Invoke(mc::DispId idMember, mc::DispParamsRef dispParams, mc::IVariantWrapperRef /* result */, mc::RefIid /* iid */)
	{		

		if ( idMember == mc::AGENTID_MAINCTXCALL )
		{
			// Jobs processing engine started in separate thread
			
			// Acquire params
			IJobsQueuePtr jobsQueue(dispParams->Get(1)->toCommon(), IID_IJobsQueue);
			mc::ISynchroPtr newSignal(dispParams->Get(0)->toCommon(), mc::IID_ISynchro);

			if ( !jobsQueue || !newSignal )
				return mc::_E_FAIL;			

			bool forever = true;
			while ( forever )
			{
				if ( mc::IsFailed(newSignal->Wait()) )
					return mc::_E_FAIL;

				newSignal->Reset();

				// Process pending jobs
				if ( mc::IsFailed(DoJobs(jobsQueue)) )
				{
					// Stop execution if internal processing routine has failed 
					break;
				}

				forever = jobsQueue->ContinueExecution();
			}
		
		} // idMember == mc::AGENTID_MAINCTXCALL

		return mc::_S_OK;
	}

	mc::result JobsContext::DoJobs(IJobsQueueRef jobsQueue)
	{
		while ( mc::IsSucceeded(jobsQueue->Execute()) );

		return mc::_S_OK;
	}

}
