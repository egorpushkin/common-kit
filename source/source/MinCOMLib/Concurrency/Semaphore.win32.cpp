#include "Common/Common.h"

#include "Semaphore.h"

#include "CommonKit/Platform.h"

namespace MinCOM
{

	class Semaphore::SemaphoreImpl_
	{
		
		friend class Semaphore;

	public:

		SemaphoreImpl_()
			: semaphore_(NULL)
		{
		}
		
		~SemaphoreImpl_()
		{
			if ( semaphore_ )
				::CloseHandle(semaphore_);
		}

		result Init(long initial, long maximum)
		{
			if ( semaphore_ )
			{
				::CloseHandle(semaphore_);
				semaphore_ = NULL;
			}

			semaphore_ = ::CreateSemaphore(NULL, initial, maximum, NULL);

			return ( semaphore_ ) ? ( _S_OK ) : ( _E_FAIL );
		}

		result AcquireSem(unsigned long milliseconds = INFINITE)
		{		
			unsigned long waitResult = ::WaitForSingleObject(semaphore_, milliseconds);

			if ( waitResult == WAIT_ABANDONED || waitResult == WAIT_FAILED )
				return _E_FAIL;

			if ( waitResult == WAIT_TIMEOUT )
				return _S_FALSE;

			// waitResult == WAIT_OBJECT_0
			return _S_OK;
		}

		result ReleaseSem(long count)
		{
			return ( ::ReleaseSemaphore(semaphore_, count, NULL) ) ? ( _S_OK ) : ( _E_FAIL );
		}

	private:

		HANDLE semaphore_;

	};

	Semaphore::Semaphore()
		: CommonImpl< ISemaphore >()
		, CommonImpl< ISynchroHandle >()
		, semaphoreImpl_(new SemaphoreImpl_)		 
	{
	}

	Semaphore::~Semaphore()
	{
	}

	// ICommon section
	BEGIN_INTERFACE_MAP(Semaphore)
		COMMON(ISemaphore)
		INTERFACE_(ISemaphore, IID_ISemaphore)
		INTERFACE__(ISemaphore, ISynchro, IID_ISynchro)
		INTERFACE_(ISynchroHandle, IID_ISynchroHandle)
	END_INTERFACE_MAP()	

	// ISemaphore section
	result Semaphore::Init(long initial, long maximum)
	{
		return semaphoreImpl_->Init(initial, maximum);
	}

	result Semaphore::AcquireSem(unsigned long milliseconds)
	{
		return semaphoreImpl_->AcquireSem(milliseconds);
	}

	result Semaphore::ReleaseSem(long count)
	{
		return semaphoreImpl_->ReleaseSem(count);
	}

	// ISynchro section
	result Semaphore::Wait(unsigned long milliseconds /* = INFINITE */)
	{
		return AcquireSem(milliseconds);
	}

	result Semaphore::Signal()
	{
		return ReleaseSem();
	}

	result Semaphore::Reset()
	{		
		return AcquireSem();
	}

	// ISynchroHandle section	
	result Semaphore::GetHandle(handle* pHandle)
	{
		if ( pHandle )
			*pHandle = semaphoreImpl_->semaphore_;
		return _S_OK;
	}

}
