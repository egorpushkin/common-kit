#include "Common/Common.h"

#include "Semaphore.h"

#include "Platforms/win32/Locale.win32.h"
#include "Platforms/win32/Concurrent.win32.h"

namespace MinCOM
{

	Semaphore::Semaphore(long initial, long maximum, const std::string& name)
		: CommonImpl< ISemaphore >()
		, semaphore_(::CreateSemaphoreW(NULL, initial, maximum, PrepareName(name)))		 
	{
		if ( !semaphore_ )
			throw std::exception();
	}

	Semaphore::Semaphore(const std::string& name)
		: CommonImpl< ISemaphore >()
		, semaphore_(::OpenSemaphoreW(EVENT_ALL_ACCESS, TRUE, LocaleWin32::A2W(name).c_str()))	
	{
		if ( !semaphore_ )
			throw std::exception();
	}

	Semaphore::~Semaphore()
	{
		if ( semaphore_ )
			::CloseHandle(semaphore_);
	}

	// ISemaphore section
	result Semaphore::Release(long count /* = 1 */)
	{
		if ( !semaphore_ )
			return _E_NOTINIT;
		long prevCount = 0;
		::ReleaseSemaphore(semaphore_, count, &prevCount);
		return _S_OK;
	}

	// ISynchro section
	result Semaphore::Wait(unsigned long delay /* = _INFINITE */)
	{
		return ConcurrentWin32::Wait(semaphore_, delay);
	}

	// Internal tools	
	const wchar_t* Semaphore::PrepareName(const std::string& name)
	{
		if ( name.length() == 0 )
			return NULL;
		return LocaleWin32::A2W(name).c_str();
	}

}
