/*
 * File name   : CoreMutex.h
 * 
 * Copyright (c) 2008 Scientific Software 
 *
 * Modification History:
 * Date        Name                Description
 * 2008-12-29  Egor Pushkin        Initial version
 */

#ifndef COREMUTEX_H__MINCOM__INCLUDED_
#define COREMUTEX_H__MINCOM__INCLUDED_

namespace MinCOM
{

	/**
	 * Minimal portable mutex implementation.
	 */
	class CoreMutex 
	{
	public:

		CoreMutex()
#if defined(WIN32)
			: mutex_(::CreateMutex(NULL, FALSE, NULL))
#elif defined(POSIX)
			: mutex_()
#endif
		{
#if defined(WIN32)
#elif defined(POSIX)
            pthread_mutexattr_t attr;
            pthread_mutexattr_init(&attr);
            pthread_mutexattr_settype(&attr, PTHREAD_MUTEX_RECURSIVE);
            pthread_mutex_init(&mutex_, &attr);
            pthread_mutexattr_destroy(&attr);            
#endif
		}

		~CoreMutex()
		{
#if defined(WIN32)
			::CloseHandle(mutex_);
#elif defined(POSIX)
			pthread_mutex_destroy(&mutex_);
#endif			
		}

		bool Lock()
		{
#if defined(WIN32)
			return SUCCEEDED(::WaitForSingleObject(mutex_, INFINITE));
#elif defined(POSIX)
			return pthread_mutex_lock(&mutex_);
#endif				
		}

		void Unlock()
		{
#if defined(WIN32)
			::ReleaseMutex(mutex_);
#elif defined(POSIX)
			pthread_mutex_unlock(&mutex_);
#endif		
		}

	private:

		/** Copy-constructor not implemented and denied. */
		CoreMutex( const CoreMutex & );
        
		/** Copy-assignment operator not implemented and denied. */
		CoreMutex & operator = ( const CoreMutex & );

	private:

#if defined(WIN32)
		HANDLE mutex_;
#elif defined(POSIX)
		pthread_mutex_t mutex_;
#endif				

	};

	class CoreMutexLock
	{
	public:

		CoreMutexLock(CoreMutex & mutex)
			: mutex_(mutex)
		{
			mutex_.Lock();
		}

		~CoreMutexLock()
		{
			mutex_.Unlock();
		}

	private:

		/** Copy-constructor not implemented and denied. */
		CoreMutexLock( const CoreMutexLock & );

		/** Copy-assignment operator not implemented and denied. */
		CoreMutexLock & operator = ( const CoreMutexLock & );

	private:

		CoreMutex & mutex_;

	};

}

#endif // !COREMUTEX_H__MINCOM__INCLUDED_
