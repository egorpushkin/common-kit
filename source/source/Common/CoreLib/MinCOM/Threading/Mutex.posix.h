#ifndef MUTEXIMPL_H__MINCOM__CORELIB__INCLUDED_
#define MUTEXIMPL_H__MINCOM__CORELIB__INCLUDED_

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

		pthread_mutex_t mutex_;
		
	};

}

#endif // !MUTEXIMPL_H__MINCOM__CORELIB__INCLUDED_
