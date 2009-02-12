#ifndef SEMAPHORE_H__MINCOMLIB__INCLUDED_
#define SEMAPHORE_H__MINCOMLIB__INCLUDED_

namespace MinCOM
{

	class Semaphore 
		: public CommonImpl< ISemaphore >
	{
	public:

		Semaphore(long initial, long maximum, const std::string& anme);
		
		Semaphore(const std::string& anme);
		
		virtual ~Semaphore();

		// ISemaphore section
		virtual result Release(long count = 1);

		// ISynchro section
		virtual result Wait(unsigned long delay = _INFINITE);

	private:

		const wchar_t* PrepareName(const std::string& name);

	private:
		
#ifdef WIN32
		/** Handle for win32 environments. */
		HANDLE semaphore_;
#elif POSIX
		/** Handle for posix environments. */
		
#endif
		
	};

}

#endif // !SEMAPHORE_H__MINCOMLIB__INCLUDED_
