#ifndef SEMAPHORE_H__MINCOMLIB__INCLUDED_
#define SEMAPHORE_H__MINCOMLIB__INCLUDED_

#if defined(POSIX)
#include <semaphore.h>
#endif

namespace MinCOM
{

	class Semaphore 
		: public CommonImpl< ISemaphore >
	{
	public:

		Semaphore(long initial, long maximum, const std::string& name);
		
		Semaphore(const std::string& name);
		
		virtual ~Semaphore();

		// ISemaphore section
		virtual result Release(long count = 1);

		// ISynchro section
		virtual result Wait(unsigned long delay = _INFINITE);

	private:

		const wchar_t* PrepareName(const std::string& name);

	private:
		
#if defined(WIN32)
		/** Handle for win32 environments. */
		HANDLE semaphore_;
#elif defined(POSIX)
		/** Handle for posix environments. */
		sem_t semaphore_;
#endif
		
	};

}

#endif // !SEMAPHORE_H__MINCOMLIB__INCLUDED_
