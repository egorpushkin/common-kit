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
		virtual result Create(bool obtain = false) = 0;

		virtual result Create(std::string name, bool obtain = false) = 0;

		virtual result Open(std::string name) = 0;

		virtual result Close() = 0;

		virtual result Release() = 0;

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
