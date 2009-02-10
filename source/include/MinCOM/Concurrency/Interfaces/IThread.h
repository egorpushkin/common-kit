/*
 * File name   : IThread.h
 *
 * Copyright (c) 2009 Scientific Software
 *
 * Modification History:
 * Date        Name                Description
 * 2009-02-10  Egor Pushkin        Initial version
 */

#ifndef ITHREAD_H__MINCOM__INCLUDED_
#define ITHREAD_H__MINCOM__INCLUDED_

namespace MinCOM
{

	/**
	 * 
	 */
	interface IThread : public ICommon
	{

		virtual result SetContext(IRunnableRef context) = 0;

		virtual result Start() = 0;

		virtual result Join() = 0;

		// Static context
		//////////////////////////////////////////////////////////////////////////
		
		static unsigned int GetCores();

		static void Sleep(unsigned long delay);

	};

	typedef Strong< IThread > IThreadPtr;
	typedef const IThreadPtr& IThreadRef;

	/*
	// Thread priority
	typedef enum tagThreadPriority
	{

		MODE_BACKGROUND_BEGIN = 0x00010000,		

		MODE_BACKGROUND_END = 0x00020000,		

		PRIORITY_ABOVE_NORMAL = 1,

		PRIORITY_BELOW_NORMAL = -1,

		PRIORITY_HIGHEST = 2,

		PRIORITY_IDLE = -15,

		PRIORITY_LOWEST = -2,

		PRIORITY_NORMAL = 0,

		PRIORITY_TIME_CRITICAL = 15

	} ThreadPriority;
	*/

}

#endif // !ITHREAD_H__MINCOM__INCLUDED_
