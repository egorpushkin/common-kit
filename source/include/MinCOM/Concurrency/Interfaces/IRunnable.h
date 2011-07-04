/*
 * File name   : IRunnable.h
 *
 * Copyright (c) 2009 Scientific Software
 *
 * Modification History:
 * Date        Name                Description
 * 2009-01-30  Egor Pushkin        Initial version
 */

#ifndef IRUNNABLE_H__MINCOM__INCLUDED_
#define IRUNNABLE_H__MINCOM__INCLUDED_

namespace MinCOM
{

	/**
	 * Provides interface for any executable operation.
	 */
	struct IRunnable : public ICommon
	{
		/**
		 * Any component calls this method to perform an operation.
		 */
		virtual result Run() = 0;
	};

	typedef Strong< IRunnable > IRunnablePtr;
	typedef const IRunnablePtr& IRunnableRef;

}

#endif // !IRUNNABLE_H__MINCOM__INCLUDED_
