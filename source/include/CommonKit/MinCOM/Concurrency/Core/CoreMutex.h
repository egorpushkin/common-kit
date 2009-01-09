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
#ifdef WIN32
			: mutex_(::CreateMutex(NULL, FALSE, NULL))
#elif POSIX
			: mutex_()
#endif
		{
#ifdef WIN32
#elif POSIX
			pthread_mutex_init(&mutex_, NULL);
#endif
		}

		~CoreMutex()
		{
#ifdef WIN32
			::CloseHandle(mutex_);
#elif POSIX
			pthread_mutex_destroy(&mutex_);
#endif			
		}

		bool Lock()
		{
#ifdef WIN32
			return SUCCEEDED(::WaitForSingleObject(mutex_, INFINITE));
#elif POSIX
			return pthread_mutex_lock(&mutex_);
#endif				
		}

		void Unlock()
		{
#ifdef WIN32
			::ReleaseMutex(mutex_);
#elif POSIX
			pthread_mutex_unlock(&mutex_);
#endif		
		}

	private:

		/** Copy-constructor not implemented and denied. */
		CoreMutex( const CoreMutex & );

		/** Copy-assignment operator not implemented and denied. */
		CoreMutex & operator = ( const CoreMutex & );

	private:

#ifdef WIN32
		HANDLE mutex_;
#elif POSIX
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
