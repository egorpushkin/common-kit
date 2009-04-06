#include "Common/Common.h"

#include "Mutex.h"

#include "Platforms/win32/Locale.win32.h"
#include "Platforms/win32/Concurrent.win32.h"

namespace MinCOM
{

	Mutex::Mutex(bool obtain, const std::string& name)
		: CommonImpl< IMutex >()
		, mutex_(NULL)
	{		
		if ( 0 != name.size() ) 
		{
			std::wstring wname(LocaleWin32::A2W(name));
			mutex_ = ::CreateMutexW(NULL, obtain, wname.c_str());
			if ( ERROR_ALREADY_EXISTS == ::GetLastError() )
				throw std::exception();
		}
		else 
			mutex_ = ::CreateMutexW(NULL, obtain, NULL);
		if ( !mutex_ )
			throw std::exception();
	}

	Mutex::Mutex(const std::string& name)
		: CommonImpl< IMutex >()
		, mutex_(NULL)
	{		
		if ( 0 == name.size() )
			throw std::exception();

		std::wstring wname(LocaleWin32::A2W(name));
		mutex_ = ::OpenMutexW(MUTEX_ALL_ACCESS, TRUE, wname.c_str());
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

}
