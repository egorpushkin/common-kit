#include "Common/Common.h"

#include "Event.h"

#include "Platforms/win32/Locale.win32.h"
#include "Platforms/win32/Concurrent.win32.h"

namespace MinCOM
{

	Event::Event()
		: CommonImpl< IEvent >()
		, event_(NULL)
	{
	}

	Event::~Event()
	{
		if ( event_ )
			::CloseHandle(event_);
	}

	// IEvent section
	result Event::Create(bool manualReset /* = true */, bool initialState /* = false */)
	{
		if ( event_ )
			return _E_ALREADYINIT;
		event_ = ::CreateEvent(NULL, manualReset, initialState, NULL);
		return ( event_ ) ? ( _S_OK ) : ( _E_FAIL );
	}

	result Event::Create(std::string name, bool manualReset /* = true */, bool initialState /* = false */)
	{
		if ( event_ )
			return _E_ALREADYINIT;
		event_ = ::CreateEvent(NULL, manualReset, initialState, LocaleWin32::A2W(name).c_str());
		return ( event_ ) ? ( _S_OK ) : ( _E_FAIL );
	}

	result Event::Open(std::string name)
	{
		if ( event_ )
			return _E_ALREADYINIT;
		event_ = ::OpenEvent(EVENT_ALL_ACCESS, TRUE, LocaleWin32::A2W(name).c_str());
		return ( event_ ) ? ( _S_OK ) : ( _E_FAIL );
	}

	result Event::Close()
	{
		if ( !event_ )
			return _E_NOTINIT;
		::CloseHandle(event_);
		event_ = NULL;
		return _S_OK;
	}

	result Event::Pulse()
	{
		if ( !event_ )
			return _E_NOTINIT;
		::PulseEvent(event_);
		return _S_OK;
	}

	result Event::Set()
	{
		if ( !event_ )
			return _E_NOTINIT;
		::SetEvent(event_);
		return _S_OK;
	}

	result Event::Reset()
	{
		::ResetEvent(event_);
		return _S_OK;
	}

	// ISynchro section
	result Event::Wait(unsigned long delay /* = _INFINITE */)
	{
		return ConcurrentWin32::Wait(event_, delay);
	}

}
