#include "Common/Common.h"

#include "Semaphore.h"

// System time.
#include <sys/time.h>

namespace MinCOM
{
    
	Semaphore::Semaphore(long initial, long /* maximum */, const std::string& name)
        : CommonImpl< ISemaphore >()
		, semaphore_(SEM_FAILED)
	{
		// Notes:
		// - sem_init seems to be not supported on Mac OS X environment.
		// - If O_EXCL is set in addition to O_CREAT, sem_open() fails if the
		// semaphore name already exists.
		// - Semapores with the same name point to the same object.
		std::string semName = name;
		if ( 0 == semName.size() )
		{
			// Unfortunately guid doed not fit the criteria of sem_open (guid
			// string representation is to long). Semaphore name is generated
			// based on the following pattern:
			// mcs_<time in milliseconds>_<object_cookie>.
			// In this case it becomes almost unique name in bounds of a process.

			// Format time.
			struct timeval tp;
			gettimeofday(&tp, NULL);
			int interval = tp.tv_sec * 1000 + tp.tv_usec / 1000;

			// Format name.
			std::stringstream nameStream;
			nameStream
				<< "mcs_"
				<< interval
				<< "_"
				<< GetCookie();
			nameStream >> semName;
		}
		semaphore_ = sem_open(semName.c_str(), O_CREAT | O_EXCL, S_IRUSR | S_IWUSR, initial);
		if ( SEM_FAILED == semaphore_ )
		{
			// errno indicates the error in this case.
			throw std::exception();
		}
	}
    
	Semaphore::Semaphore(const std::string& /* name */)
        : CommonImpl< ISemaphore >()
        , semaphore_()
	{
		// TODO: Open POSIX semaphore!
		// if ( !mutex_ )
		//	throw std::exception();
	}
    
	Semaphore::~Semaphore()
	{
		// sem_destroy(&semaphore_);
		if ( SEM_FAILED != semaphore_ )
			sem_close(semaphore_);
	}
    
	// ISemaphore section
	result Semaphore::Release(long count /* = 1 */)
	{
		for ( long i = 0 ; i < count ; ++i )
        {
			int ret = sem_post(semaphore_);
			if ( 0 != ret )
				return _E_FAIL;
        }		
		return _S_OK;
	}
    
	// ISynchro section
	result Semaphore::Wait(unsigned long /* delay *//* = _INFINITE */)
	{
		int ret = sem_wait(semaphore_);
		if ( 0 != ret )
			return _E_FAIL;
		return _S_OK;
	}
    
    result Semaphore::Close()
    {
        return _E_NOTIMPL;
    }
 		
}
