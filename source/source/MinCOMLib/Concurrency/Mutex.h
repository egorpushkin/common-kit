#ifndef MUTEX_H__MINCOM__INCLUDED_
#define MUTEX_H__MINCOM__INCLUDED_

namespace MinCOM
{

	class Mutex 
		: public CommonImpl< IMutex >
	{
	public:

		Mutex();
		virtual ~Mutex();

		// IMutex section
		virtual result Create(bool obtain = false);

		virtual result Create(std::string name, bool obtain = false);

		virtual result Open(std::string name);

		virtual result Close();

		virtual result Release();

		// ISynchro section
		virtual result Wait(unsigned long delay = _INFINITE);

	private:

#ifdef WIN32
		/** Handle for win32 environments. */
		HANDLE mutex_;
#elif POSIX
		/** Handle for posix environments. */
		
#endif
		
	};

}

#endif // !MUTEX_H__MINCOM__INCLUDED_
