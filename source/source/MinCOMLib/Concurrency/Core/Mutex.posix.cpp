#include "Common/Common.h"

#include "Mutex.h"

namespace MinCOM
{
    
	Mutex::Mutex(bool /* obtain */, const std::string& name)
        : CommonImpl< IMutex >()
        , named_(false)
        , mutex_()
		, name_(name)
        , semaphore_(NULL)
        , opened_(false)
	{
        // Check whether mutex object should be named.
        if ( 0 == name.size() )
        {
            // Use regular posix mutex for inner-process synchronization.
            pthread_mutexattr_t attr;
            pthread_mutexattr_init(&attr);
            pthread_mutexattr_settype(&attr, PTHREAD_MUTEX_RECURSIVE);
            pthread_mutex_init(&mutex_, &attr);
            pthread_mutexattr_destroy(&attr);
            // TODO: Check whether mutex is created.
        }
        else
        {
            // Use named posix semaphores mutex for inter-process synchronization.
            semaphore_ = sem_open(name.c_str(), O_CREAT | O_EXCL, S_IRUSR | S_IWUSR, 0);
            if ( SEM_FAILED == semaphore_ )
                // Notify caller on failure. This is probably caused by occupied name.
                // In this case Mutex object must not be constructed.
                throw std::exception();
            named_ = true;
        }
	}
    
	Mutex::Mutex(const std::string& name)
        : CommonImpl< IMutex >()
        , named_(true)
        , mutex_()
		, name_(name)
        , semaphore_(NULL)
        , opened_(true)
	{
        // Open named semaphore.
        semaphore_ = sem_open(name.c_str(), 0, 0, 0);
        if ( SEM_FAILED == semaphore_ )
            // Notify caller on failure. This is probably caused by wrong name.
            // In this case Mutex object must not be constructed.
            throw std::exception();
        named_ = true;
	}
    
	Mutex::~Mutex()
	{
        if ( !named_ )
            pthread_mutex_destroy(&mutex_);
        else
		{
            sem_close(semaphore_);
			if ( !opened_ )
				sem_unlink(name_.c_str());
		}
	}
    
	// IMutex section
	result Mutex::Release()
	{
        if ( !named_ )
            pthread_mutex_unlock(&mutex_);
        else
            sem_post(semaphore_);
		return _S_OK;
	}
    
	// ISynchro section
	result Mutex::Wait(unsigned long /* delay *//* = _INFINITE */)
	{
		int code = 0;
        if ( !named_ )
            code = pthread_mutex_lock(&mutex_);
        else
            code = sem_wait(semaphore_);
		return ( !code ) ? ( _S_OK ) : ( _E_FAIL );
	}
    
    result Mutex::Close()
    {
        return _E_NOTIMPL;
    }
 		
}
