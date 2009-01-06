#include "Common/Common.h"

#include "Event.h"

#include "CommonKit/Platform.h"

namespace MinCOM
{

	class Event::EventImpl_
	{
		
		friend class Event;

	public:

		EventImpl_()
			: event_(::CreateEvent(NULL, TRUE, FALSE, NULL))
		{
		}
		
		~EventImpl_()
		{
			if ( event_ )
				::CloseHandle(event_);
		}

		void Set()
		{		
			::SetEvent(event_);
		}

		void Reset()
		{
			::ResetEvent(event_);
		}

		result Wait(unsigned long milliseconds)
		{		
			unsigned long waitResult = ::WaitForSingleObject(event_, milliseconds);
			
			if ( waitResult == WAIT_ABANDONED || waitResult == WAIT_FAILED )
				return _E_FAIL;

			if ( waitResult == WAIT_TIMEOUT )
				return _S_FALSE;
			
			// waitResult == WAIT_OBJECT_0
			return _S_OK;
		}

		void Pulse()
		{
			::PulseEvent(event_);
		}
	
	private:

		HANDLE event_;

	};

	Event::Event()
		: CommonImpl< IEvent >()
		, CommonImpl< ISynchroHandle >()
		, eventImpl_(new EventImpl_)
	{
	}

	Event::~Event()
	{
	}

	// ICommon section
	BEGIN_INTERFACE_MAP(Event)
		COMMON(IEvent)
		INTERFACE_(IEvent, IID_IEvent)
		INTERFACE__(IEvent, ISynchro, IID_ISynchro)
		INTERFACE_(ISynchroHandle, IID_ISynchroHandle)
	END_INTERFACE_MAP()	

	// IEvent section
	result Event::Pulse()
	{
		eventImpl_->Pulse();
	
		return _S_OK;
	}

	// ISynchro section
	result Event::Wait(unsigned long milliseconds /* = INFINITE */)
	{
		return eventImpl_->Wait(milliseconds);
	}

	result Event::Signal()
	{
		eventImpl_->Set();

		return _S_OK;
	}

	result Event::Reset()
	{
		eventImpl_->Reset();

		return _S_OK;
	}

	// ISynchroHandle section	
	result Event::GetHandle(handle* pHandle)
	{
		*pHandle = eventImpl_->event_;
		return _S_OK;
	}

}
