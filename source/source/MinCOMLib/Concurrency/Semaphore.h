#ifndef SEMAPHORE_H__MINCOM__CORELIB__INCLUDED_
#define SEMAPHORE_H__MINCOM__CORELIB__INCLUDED_

namespace MinCOM
{

	class Semaphore 
		: public CommonImpl< ISemaphore >
		, public CommonImpl< ISynchroHandle >
	{
	public:

		Semaphore();
		virtual ~Semaphore();

		// ICommon section
		DECLARE_INTERFACE_MAP()		

		// ISemaphore section
		virtual result Init(long initial, long maximum);

		virtual result AcquireSem(unsigned long milliseconds = _INFINITE);

		virtual result ReleaseSem(long count = 1);

		// ISynchro section
		virtual result Wait(unsigned long milliseconds = _INFINITE);

		virtual result Signal();

		virtual result Reset();

		// ISynchroHandle section	
		virtual result GetHandle(handle* pHandle);

	private:
		
		class SemaphoreImpl_;	

		typedef Loki::SmartPtr< SemaphoreImpl_ > SemaphoreImplPtr_;

		SemaphoreImplPtr_ semaphoreImpl_;
		
	};

}

#endif // !SEMAPHORE_H__MINCOM__CORELIB__INCLUDED_
