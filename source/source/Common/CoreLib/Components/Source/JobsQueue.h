#ifndef JOBQUEUE_H__COMPONENTS__CORELIB__INCLUDED_
#define JOBQUEUE_H__COMPONENTS__CORELIB__INCLUDED_

namespace Components
{

	class JobsQueue 
		: public mc::CommonImpl< IJobsQueue >
		, public mc::CommonImpl< mc::ISynchro >
		, public mc::ItemImpl
	{

		typedef Project::ContainerImpl ContainerImpl_;

	public:

		JobsQueue();
		virtual ~JobsQueue();

		// ICommon section
		DECLARE_INTERFACE_MAP()		

		// IJobsQueue section
		virtual mc::result Start();

		virtual mc::result Stop();

		virtual mc::result Push(mc::IAgentRef jobExec, mc::DispParamsRef params = NULL);

		virtual mc::result Execute();

		virtual bool ContinueExecution();

		// ISynchro section
		virtual mc::result Wait(unsigned long milliseconds = mc::_INFINITE);

		virtual mc::result Signal();

		virtual mc::result Reset();

	private:

		typedef struct tagJob_
		{

			mc::IAgentPtr jobExecutor_;

			mc::DispParamsPtr params_;

		} Job_;

		typedef Loki::SmartPtr< Job_ > JobPtr_; 

		// Private tools
		JobPtr_ Pop();

	private:

		mc::IMutexPtr lockStartStop_;

		mc::IMutexPtr lockQueue_;

		mc::IThreadPtr workingThread_;

		mc::IEventPtr newJobSignal_;

		std::queue< JobPtr_ > jobs_;

		bool continueExecution_;

	};

}

#endif // !JOBQUEUE_H__COMPONENTS__CORELIB__INCLUDED_
