#ifndef JOBSCONTEXT_H__COMPONENTS__CORELIB__INCLUDED_
#define JOBSCONTEXT_H__COMPONENTS__CORELIB__INCLUDED_

namespace Components
{

	class JobsContext
		: public mc::AgentImpl
	{
	public:

		JobsContext();
		virtual ~JobsContext();

		// IAgent section
		virtual mc::result Invoke(mc::DispId idMember, mc::DispParamsRef dispParams, mc::IVariantWrapperRef result, mc::RefIid iid);

	private:

		mc::result DoJobs(IJobsQueueRef jobsQueue);

	};

}

#endif // !JOBSCONTEXT_H__COMPONENTS__CORELIB__INCLUDED_