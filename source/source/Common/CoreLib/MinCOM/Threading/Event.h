#ifndef EVENT_H__MINCOM__CORELIB__INCLUDED_
#define EVENT_H__MINCOM__CORELIB__INCLUDED_

namespace MinCOM
{

	class Event 
		: public CommonImpl< IEvent >
		, public CommonImpl< ISynchroHandle >
	{
	public:

		Event();
		virtual ~Event();

		// ICommon section
		DECLARE_INTERFACE_MAP()		

		// IEvent section
		virtual result Pulse();

		// ISynchro section
		virtual result Wait(unsigned long milliseconds = INFINITE);

		virtual result Signal();

		virtual result Reset();

		// ISynchroHandle section	
		virtual result GetHandle(handle* pHandle);

	private:
		
		class EventImpl_;	

		typedef Loki::SmartPtr< EventImpl_ > EventImplPtr_;

		EventImplPtr_ eventImpl_;
		
	};

}

#endif // !EVENT_H__MINCOM__CORELIB__INCLUDED_
