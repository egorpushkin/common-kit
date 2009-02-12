/*
 * File name   : IJobsQueue.h
 *
 * Copyright (c) 2009 Scientific Software
 *
 * Modification History:
 * Date        Name                Description
 * 2009-02-11  Egor Pushkin        Initial version
 */

#ifndef IJOBSQUEUE_H__MINCOM__INCLUDED_
#define IJOBSQUEUE_H__MINCOM__INCLUDED_

namespace MinCOM
{

	interface IJobsQueue : public ICommon
	{

		virtual result Run() = 0;

		virtual result Stop() = 0;

		virtual result Push(IRunnableRef job) = 0;

		virtual result Execute() = 0;

		virtual bool ContinueExecution() = 0;

	};

	typedef Strong< IJobsQueue > IJobsQueuePtr;
	typedef const IJobsQueuePtr& IJobsQueueRef;

}

#endif // !IJOBSQUEUE_H__MINCOM__INCLUDED_
