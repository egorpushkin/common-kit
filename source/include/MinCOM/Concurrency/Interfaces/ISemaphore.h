/*
 * File name   : IJobsQueue.h
 *
 * Copyright (c) 2009 Scientific Software
 *
 * Modification History:
 * Date        Name                Description
 * 2009-02-11  Egor Pushkin        Initial version
 */

#ifndef ISEMAPHORE_H__MINCOM__INCLUDED_
#define ISEMAPHORE_H__MINCOM__INCLUDED_

namespace MinCOM
{

	interface ISemaphore : public ISynchro
	{
		
		virtual result Release(long count = 1) = 0;
	};

	typedef Strong< ISemaphore > ISemaphorePtr;
	typedef const ISemaphorePtr& ISemaphoreRef;

}

#endif // !ISEMAPHORE_H__MINCOM__INCLUDED_
