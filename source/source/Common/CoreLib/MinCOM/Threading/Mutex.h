#ifndef MUTEX_H__MINCOM__CORELIB__INCLUDED_
#define MUTEX_H__MINCOM__CORELIB__INCLUDED_

namespace MinCOM
{

	class MutexImpl;	

	typedef Loki::SmartPtr< MutexImpl > MutexImplPtr;

	class Mutex 
		: public CommonImpl< IMutex >
		, public CommonImpl< ISynchroHandle >
	{
	public:

		Mutex();

		// ICommon section
		DECLARE_INTERFACE_MAP()		

		// IMutex section
		virtual result Enter(unsigned long milliseconds = _INFINITE);

		virtual result Leave();

		// ISynchro section
		virtual result Wait(unsigned long milliseconds = _INFINITE);

		virtual result Signal();

		virtual result Reset();

		// ISynchroHandle section	
		virtual result GetHandle(handle* pHandle);

	private:

		MutexImplPtr mutexImpl_;
		
	};

}

#endif // !MUTEX_H__MINCOM__CORELIB__INCLUDED_
