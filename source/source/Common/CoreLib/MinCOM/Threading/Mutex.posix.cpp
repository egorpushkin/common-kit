#include "Common/Common.h"

#include <pthread.h>

#include "Mutex.posix.h"

namespace MinCOM
{

	MutexImpl::MutexImpl()
		: mutex_()
	{
		pthread_mutex_init(&mutex_, NULL);
	}
		
	MutexImpl::~MutexImpl()
	{
		pthread_mutex_destroy(&mutex_);
	}

	result MutexImpl::Enter(unsigned long milliseconds /* = _INFINITE */)
	{		
		int code = pthread_mutex_lock(&mutex_);
		if ( code )
			return _E_FAIL;

		return _S_OK;
	}

	void MutexImpl::Leave()
	{
		pthread_mutex_unlock(&mutex_);
	}
	
	void* MutexImpl::toHandle()
	{
		return &mutex_;
	}
		
}
