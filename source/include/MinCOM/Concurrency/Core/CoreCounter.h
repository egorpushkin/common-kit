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
#if defined(WIN32)
			return ( 0 == ::InterlockedCompareExchange(&value, value, 0) );
#elif defined(POSIX)
            // TODO: Implement this in thread safe manner.
            return ( 0 == value );
#endif
		}

		static long Increment(long & value)
		{
#if defined(WIN32)
			return ::InterlockedIncrement(&value);
#elif defined(POSIX)
            return __sync_add_and_fetch(&value, 1);
#endif
		}

		static long Decrement(long & value)
		{
#if defined(WIN32)
			return ::InterlockedDecrement(&value);
#elif defined(POSIX)
            return __sync_sub_and_fetch(&value, 1);
#endif
		}
	};

}

#endif // !CORECOUNTER_H__MINCOM__INCLUDED_
