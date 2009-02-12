/*
 * File name   : Library.h
 *
 * Copyright (c) 2009 Scientific Software
 *
 * Modification History:
 * Date        Name                Description
 * 2009-02-03  Egor Pushkin        Initial version
 */

#ifndef LIBRARY_H__MINCOM__INCLUDED_
#define LIBRARY_H__MINCOM__INCLUDED_

namespace MinCOM
{

	/**
	 * Tool to provide common and simple way to instantiate internal
	 * MinCOM objects. Each method of this tool finally makes the following
	 * call:
	 *
	 * \code
	 *     Class< mc::SomeObject >::Create( arguments_if_any );
	 * \endcode
	 *
	 * This is caused by the fact that most implementations are not publicitly 
	 * visible due to architectural aspects. So this tool just simplifies 
	 * producing such objects.
	 */ 
	class Library
	{
	public:

		static ICommandsPtr Commands();

		static IVectorPtr Vector();

		static IListPtr List();

		// Events
		//////////////////////////////////////////////////////////////////////////

/*		static IEventPtr Event(bool manualReset = true, bool initialState = false, const std::string& name = std::string());

		static IEventPtr EventOpen(const std::string& name); */

		// Mutexes
		//////////////////////////////////////////////////////////////////////////

		static IMutexPtr Mutex(bool obtain = false, const std::string& name = std::string());

		static IMutexPtr MutexOpen(const std::string& name);

		// Semaphores
		//////////////////////////////////////////////////////////////////////////

		static ISemaphorePtr Semaphore(long initial, long maximum, const std::string& name = std::string());

		static ISemaphorePtr SemaphoreOpen(const std::string& name);

		static IThreadPtr Thread();

		static IJobsQueuePtr JobsQueue();

		static IServicePtr Service();

		static IConnectionPtr TCPConnection(IServiceRef service);

		static IFactoryPtr Factory();

	};

}

#endif // !LIBRARY_H__MINCOM__INCLUDED_
