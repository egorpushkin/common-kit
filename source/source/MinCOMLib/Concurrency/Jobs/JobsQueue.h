#ifndef JOBQUEUE_H__MINCOMLIB__INCLUDED_
#define JOBQUEUE_H__MINCOMLIB__INCLUDED_

namespace MinCOM
{

	class JobsQueue 
		: public mc::CommonImpl< IJobsQueue >
		, public mc::CommonImpl< ISynchro >
	{
    public:

        typedef CommonImpl< IJobsQueue > ClassRoot_;

		JobsQueue();
		virtual ~JobsQueue();

		// IJobsQueue section
		virtual result Run();

		virtual result Stop();

		virtual result Push(IRunnableRef job);

		virtual result Execute();

		virtual bool ContinueExecution();

		// ISynchro section
		virtual result Wait(unsigned long delay = _INFINITE);

		virtual result Close();

	protected:

		// Internal tools
		IRunnablePtr Pop();

	private:

		IThreadPtr workingThread_;

		ISemaphorePtr jobsCounter_;

		std::queue< IRunnablePtr > jobs_;

		bool continueExecution_;

	};

}

#endif // !JOBQUEUE_H__MINCOMLIB__INCLUDED_
