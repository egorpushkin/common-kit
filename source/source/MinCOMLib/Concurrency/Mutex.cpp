#include "Common/Common.h"

#include "Mutex.h"

#ifdef _MSC_VER
#include "CommonKit/Platform.h"
#include "Mutex.win32.h"
#else // Posix threads
#include <pthread.h>
#include "Mutex.posix.h"
#endif

namespace MinCOM
{

	Mutex::Mutex()
		: CommonImpl< IMutex >()
		, CommonImpl< ISynchroHandle >()
		, mutexImpl_(new MutexImpl())		 
	{
	}

	// ICommon section
	BEGIN_INTERFACE_MAP(Mutex)
		COMMON(IMutex)
		INTERFACE_(IMutex, IID_IMutex)
		INTERFACE__(IMutex, ISynchro, IID_ISynchro)
		INTERFACE_(ISynchroHandle, IID_ISynchroHandle)
	END_INTERFACE_MAP()	

	// IMutex section
	result Mutex::Enter(unsigned long milliseconds /* = _INFINITE */)
	{
		return mutexImpl_->Enter(milliseconds);
	}

	result Mutex::Leave()
	{
		mutexImpl_->Leave();

		return _S_OK;
	}

	// ISynchro section
	result Mutex::Wait(unsigned long milliseconds /* = _INFINITE */)
	{
		return Enter(milliseconds);
	}

	result Mutex::Signal()
	{
		return Leave();
	}

	result Mutex::Reset()
	{		
		return Enter();
	}

	// ISynchroHandle section	
	result Mutex::GetHandle(handle* pHandle)
	{
		if ( pHandle )
			*pHandle = mutexImpl_->toHandle();
			
		return _S_OK;
	}

}
