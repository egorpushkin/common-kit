#ifndef MUTEX_H__MINCOM__INCLUDED_
#define MUTEX_H__MINCOM__INCLUDED_

namespace MinCOM
{

	class Mutex 
		: public CommonImpl< IMutex >
	{
	public:

		Mutex(bool obtain, const std::string& name);

		Mutex(const std::string& name);

		virtual ~Mutex();

		// IMutex section
		virtual result Release();

		// ISynchro section
		virtual result Wait(unsigned long delay = _INFINITE);

	private:

		const wchar_t* PrepareName(const std::string& name);

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
