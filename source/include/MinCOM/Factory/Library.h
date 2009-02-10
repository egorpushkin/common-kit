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
	 *     mc::FactoryHolder::Instance()->Create( 
	 *         mc::Class< mc::ISomeInterface >::DefaultClsid() );
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

		static IEventPtr Event();

		static IMutexPtr Mutex();

		static IThreadPtr Thread();

		static IServicePtr Service();

		static IConnectionPtr TCPConnection(IServiceRef service);


	};

}

#endif // !LIBRARY_H__MINCOM__INCLUDED_
