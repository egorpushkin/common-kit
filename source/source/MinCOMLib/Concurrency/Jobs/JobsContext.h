#ifndef JOBSCONTEXT_H__MINCOMLIB__INCLUDED_
#define JOBSCONTEXT_H__MINCOMLIB__INCLUDED_

namespace MinCOM
{

	class JobsContext
		: public CommonImpl< IRunnable >
	{
	public:

		JobsContext(IJobsQueueRef jobsQueue, IEventRef newJobSignal);

		// IRunnable section
		virtual result Run();

	private:

		result DoJobs(IJobsQueueRef jobsQueue);

	private:

		IJobsQueueRef jobsQueue_;
		
		IEventRef newJobSignal_;

	};

}

#endif // !JOBSCONTEXT_H__MINCOMLIB__INCLUDED_
