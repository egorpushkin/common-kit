#ifndef EVENT_H__MINCOM__INCLUDED_
#define EVENT_H__MINCOM__INCLUDED_

namespace MinCOM
{

	class Event 
		: public CommonImpl< IEvent >
	{
	public:

		Event(bool manualReset, bool initialState, const std::string& name);

		Event(const std::string& name);

		virtual ~Event();

		// IEvent section
		virtual result Pulse();

		virtual result Set();

		virtual result Reset();

		// ISynchro section
		virtual result Wait(unsigned long delay = _INFINITE);

	private:

		const wchar_t* PrepareName(const std::string& name);

	private:

#ifdef WIN32
		/** Handle for win32 environments. */
		HANDLE event_;
#elif POSIX
		/** Handle for posix environments. */
		
#endif
		
	};

}

#endif // !EVENT_H__MINCOM__INCLUDED_
