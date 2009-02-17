#include "Common/Common.h"

#include "Mutex.h"

namespace MinCOM
{
    
	Mutex::Mutex(bool obtain, const std::string& name)
        : CommonImpl< IMutex >()
        , mutex_()
	{
        pthread_mutexattr_t attr;
        pthread_mutexattr_init(&attr);
        pthread_mutexattr_settype(&attr, PTHREAD_MUTEX_RECURSIVE);
        
        pthread_mutex_init(&mutex_, &attr);
        
        pthread_mutexattr_destroy(&attr);
        // TODO: Check whether mutex is created.
	}
    
	Mutex::Mutex(const std::string& name)
        : CommonImpl< IMutex >()
        , mutex_()
	{
        // TODO: Open POSIX mutex!
		// if ( !mutex_ )
		//	throw std::exception();
	}
    
	Mutex::~Mutex()
	{
		pthread_mutex_destroy(&mutex_);
	}
    
	// IMutex section
	result Mutex::Release()
	{
		pthread_mutex_unlock(&mutex_);
		return _S_OK;
	}
    
	// ISynchro section
	result Mutex::Wait(unsigned long delay /* = _INFINITE */)
	{
		int code = pthread_mutex_lock(&mutex_);
		if ( code )
			return _E_FAIL;        
		return _S_OK;
	}
 		
}
