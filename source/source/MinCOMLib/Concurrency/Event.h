#ifndef EVENT_H__MINCOM__INCLUDED_
#define EVENT_H__MINCOM__INCLUDED_

namespace MinCOM
{

	class Event 
		: public CommonImpl< IEvent >
	{
	public:

		Event();
		virtual ~Event();

		// IEvent section
		virtual result Create(bool manualReset = true, bool initialState = false);

		virtual result Create(std::string name, bool manualReset = true, bool initialState = false);

		virtual result Open(std::string name);

		virtual result Close();

		virtual result Pulse();

		virtual result Set();

		virtual result Reset();

		// ISynchro section
		virtual result Wait(unsigned long delay = _INFINITE);

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
