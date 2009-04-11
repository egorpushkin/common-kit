#include "Common/Common.h"

#include "Semaphore.h"

namespace MinCOM
{
    
	Semaphore::Semaphore(long initial, long maximum, const std::string& name)
        : CommonImpl< ISemaphore >()
        , semaphore_()
	{
        sem_init(&semaphore_, true, initial);
        // TODO: Check whether semaphore is created.
	}
    
	Semaphore::Semaphore(const std::string& name)
        : CommonImpl< ISemaphore >()
        , semaphore_()
	{
        // TODO: Open POSIX mutex!
		// if ( !mutex_ )
		//	throw std::exception();
	}
    
	Semaphore::~Semaphore()
	{
		sem_destroy(&semaphore_);
	}
    
	// IMutex section
	result Semaphore::Release(long count /* = 1 */)
	{
        for ( long i = 0 ; i < count ; ++i )
        {
            sem_post(&semaphore_);
        }		
		return _S_OK;
	}
    
	// ISynchro section
	result Semaphore::Wait(unsigned long delay /* = _INFINITE */)
	{
		int code = sem_wait(&semaphore_);
		if ( 0 != code )
			return _E_FAIL;        
		return _S_OK;
	}
    
    result Semaphore::Close()
    {
        return _E_NOTIMPL;
    }
 		
}
