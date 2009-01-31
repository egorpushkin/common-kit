#include "Common/Common.h"

#include "Mutex.win32.h"

#include "CommonKit/Platform.h"

namespace MinCOM
{

	MutexImpl::MutexImpl()
		: mutex_(::CreateMutex(NULL, FALSE, NULL))
	{
	}

	MutexImpl::~MutexImpl()
	{
		if ( mutex_ )
			::CloseHandle(mutex_);
	}

	result MutexImpl::Enter(unsigned long milliseconds /* = _INFINITE */)
	{		
		unsigned long waitResult = ::WaitForSingleObject(mutex_, milliseconds);

		if ( waitResult == WAIT_ABANDONED || waitResult == WAIT_FAILED )
			return _E_FAIL;

		if ( waitResult == WAIT_TIMEOUT )
			return _S_FALSE;

		// waitResult == WAIT_OBJECT_0
		return _S_OK;
	}

	void MutexImpl::Leave()
	{
			::ReleaseMutex(mutex_);
	}

	void* MutexImpl::toHandle()
	{
		return mutex_;
	}

}
