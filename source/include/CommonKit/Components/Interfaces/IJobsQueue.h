#ifndef IJOBSQUEUE_H__COMPONENTS__COMMONKIT__INCLUDED_
#define IJOBSQUEUE_H__COMPONENTS__COMMONKIT__INCLUDED_

namespace Components
{

	interface IJobsQueue : public mc::ICommon
	{

		virtual mc::result Start() = 0;

		virtual mc::result Stop() = 0;

		virtual mc::result Push(mc::IAgentRef jobExec, mc::DispParamsRef params = NULL) = 0;

		virtual mc::result Execute() = 0;

		virtual bool ContinueExecution() = 0;

	};

	typedef mc::ComPtr< IJobsQueue > IJobsQueuePtr;
	typedef const IJobsQueuePtr& IJobsQueueRef;

	// {6fc2e099-3f36-4675-8233-1d45180309cf} 
	MC_DEFINE_GUID(IID_IJobsQueue, 
	0x6fc2e099, 0x3f36, 0x4675, 0x82, 0x33, 0x1d, 0x45, 0x18, 0x03, 0x09, 0xcf);

	// Job events
	enum 
	{

		AGENTID_MAINJOBCALL = 0xff010B01

	};

	IJobsQueuePtr InstantiateJobsQueue();

}

#endif // !IJOBSQUEUE_H__COMPONENTS__COMMONKIT__INCLUDED_