#include "Common/Common.h"

#include "Mutex.h"

#include "Platforms/win32/Locale.win32.h"
#include "Platforms/win32/Concurrent.win32.h"

namespace MinCOM
{

	Mutex::Mutex()
		: CommonImpl< IMutex >()
		, mutex_(NULL)
	{
	}

	Mutex::~Mutex()
	{
		if ( mutex_ )
			::CloseHandle(mutex_);
	}

	// IMutex section
	result Mutex::Create(bool obtain /* = false */)
	{
		if ( mutex_ )
			return _E_ALREADYINIT;
		mutex_ = ::CreateMutex(NULL, obtain, NULL);
		return ( mutex_ ) ? ( _S_OK ) : ( _E_FAIL );
	}

	result Mutex::Create(std::string name, bool obtain /* = false */)
	{
		if ( mutex_ )
			return _E_ALREADYINIT;
		mutex_ = ::CreateMutex(NULL, obtain, LocaleWin32::A2W(name).c_str());
		return ( mutex_ ) ? ( _S_OK ) : ( _E_FAIL );
	}

	result Mutex::Open(std::string name)
	{
		if ( mutex_ )
			return _E_ALREADYINIT;
		mutex_ = ::OpenEvent(MUTEX_ALL_ACCESS, TRUE, LocaleWin32::A2W(name).c_str());
		return ( mutex_ ) ? ( _S_OK ) : ( _E_FAIL );
	}

	result Mutex::Close()
	{
		if ( !mutex_ )
			return _E_NOTINIT;
		::CloseHandle(mutex_);
		mutex_ = NULL;
		return _S_OK;
	}

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
