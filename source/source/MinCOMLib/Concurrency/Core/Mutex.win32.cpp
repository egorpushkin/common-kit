#include "Common/Common.h"

#include "Mutex.h"

#include "Platforms/win32/Locale.win32.h"
#include "Platforms/win32/Concurrent.win32.h"

namespace MinCOM
{

	Mutex::Mutex(bool obtain, const std::string& name)
		: CommonImpl< IMutex >()
		, mutex_(::CreateMutexW(NULL, obtain, PrepareName(name)))
	{
		if ( !mutex_ )
			throw std::exception();
	}

	Mutex::Mutex(const std::string& name)
		: CommonImpl< IMutex >()
		, mutex_(::OpenEventW(MUTEX_ALL_ACCESS, TRUE, LocaleWin32::A2W(name).c_str()))
	{
		if ( !mutex_ )
			throw std::exception();
	}

	Mutex::~Mutex()
	{
		if ( mutex_ )
			::CloseHandle(mutex_);
	}

	// IMutex section
	result Mutex::Release()
	{
		if ( !mutex_ )
			return _E_NOTINIT;
		::ReleaseMutex(mutex_);
		return _S_OK;
	}

	// ISynchro section
	result Mutex::Wait(unsigned long delay /* = _INFINITE */)
	{
		return ConcurrentWin32::Wait(mutex_, delay);
	}

	// Internal tools	
	const wchar_t* Mutex::PrepareName(const std::string& name)
	{
		if ( name.length() == 0 )
			return NULL;
		return LocaleWin32::A2W(name).c_str();
	}

}
