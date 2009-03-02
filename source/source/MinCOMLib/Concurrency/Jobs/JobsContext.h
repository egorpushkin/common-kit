#ifndef JOBSCONTEXT_H__MINCOMLIB__INCLUDED_
#define JOBSCONTEXT_H__MINCOMLIB__INCLUDED_

namespace MinCOM
{

	class JobsContext
		: public CommonImpl< IRunnable >
	{
	public:

		JobsContext(IJobsQueueRef jobsQueue, ISemaphoreRef jobsCounter);

		// IRunnable section
		virtual result Run();

	private:

		IJobsQueueWeak jobsQueue_;
		
		ISemaphorePtr jobsCounter_;

	};

}

#endif // !JOBSCONTEXT_H__MINCOMLIB__INCLUDED_
