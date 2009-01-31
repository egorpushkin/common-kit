/*
 * File name   : CoreMutex.h
 * 
 * Copyright (c) 2008 Scientific Software 
 *
 * Modification History:
 * Date        Name                Description
 * 2008-12-29  Egor Pushkin        Initial version
 */

#ifndef CORECOUNTER_H__MINCOM__INCLUDED_
#define CORECOUNTER_H__MINCOM__INCLUDED_

namespace MinCOM
{
	
	/**
	 * Provides portable thread safe counter.
	 */
	class CoreCounter
	{
	public:

		static bool TestZero(long & value)
		{
#ifdef WIN32
			return ( 0 == ::InterlockedCompareExchange(&value, value, 0) );
#elif POSIX

#endif
		}

		static long Increment(long & value)
		{
#ifdef WIN32
			return ::InterlockedIncrement(&value);
#elif POSIX

#endif
		}

		static long Decrement(long & value)
		{
#ifdef WIN32
			return ::InterlockedDecrement(&value);
#elif POSIX

#endif
		}
	};

}

#endif // !CORECOUNTER_H__MINCOM__INCLUDED_
