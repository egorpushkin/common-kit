/*
 * File name   : SemaphoreScopeRelease.h
 *
 * Copyright (c) 2009 Scientific Software
 *
 * Modification History:
 * Date        Name                Description
 * 2009-04-10  Egor Pushkin        Initial version
 */

#ifndef SEMAPHORESCOPERELEASE_H__MINCOM__INCLUDED_
#define SEMAPHORESCOPERELEASE_H__MINCOM__INCLUDED_

namespace MinCOM
{

	class SemaphoreScopeRelease
	{
	public:

		SemaphoreScopeRelease(ISemaphoreRef semaphore, long count = 1);
		~SemaphoreScopeRelease();

	private:

		ISemaphorePtr semaphore_;

		long count_;

	};

}

#endif // !SEMAPHORESCOPERELEASE_H__MINCOM__INCLUDED_
