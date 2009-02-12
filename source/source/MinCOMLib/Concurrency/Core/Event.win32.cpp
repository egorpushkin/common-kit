#include "Common/Common.h"

#include "Event.h"

#include "Platforms/win32/Locale.win32.h"
#include "Platforms/win32/Concurrent.win32.h"

namespace MinCOM
{

	Event::Event(bool manualReset, bool initialState, const std::string& name)
		: CommonImpl< IEvent >()
		, event_(::CreateEventW(NULL, manualReset, initialState, PrepareName(name)))
	{
		if ( !event_ )
			throw std::exception();
	}

	Event::Event(const std::string& name)
		: CommonImpl< IEvent >()
		, event_(::OpenEventW( EVENT_ALL_ACCESS, TRUE, LocaleWin32::A2W(name).c_str()))
	{
		if ( !event_ )
			throw std::exception();
	}

	Event::~Event()
	{
		if ( event_ )
			::CloseHandle(event_);
	}

	// IEvent section
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

	// Internal tools	
	const wchar_t* Event::PrepareName(const std::string& name)
	{
		if ( name.length() == 0 )
			return NULL;
		return LocaleWin32::A2W(name).c_str();
	}

}
