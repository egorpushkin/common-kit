#ifndef MUTEX_WIN32_H__MINCOM__CORELIB__INCLUDED_
#define MUTEX_WIN32_H__MINCOM__CORELIB__INCLUDED_

namespace MinCOM
{

	class MutexImpl
	{

		friend class Mutex;

	public:

		MutexImpl();	

		~MutexImpl();

		result Enter(unsigned long milliseconds = _INFINITE);

		void Leave();

	private:

		void* toHandle();

	private:

		HANDLE mutex_;

	};

}

#endif // !MUTEX_WIN32_H__MINCOM__CORELIB__INCLUDED_