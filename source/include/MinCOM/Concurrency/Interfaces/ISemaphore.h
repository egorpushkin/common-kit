#ifndef ISEMAPHORE_H__MINCOM__COMMONKIT__INCLUDED_
#define ISEMAPHORE_H__MINCOM__COMMONKIT__INCLUDED_

namespace MinCOM
{

	interface ISemaphore : public ISynchro
	{

		virtual result Init(long initial, long maximum) = 0;

		virtual result AcquireSem(unsigned long milliseconds = _INFINITE) = 0;

		virtual result ReleaseSem(long count = 1) = 0;

	};

	typedef ComPtr< ISemaphore > ISemaphorePtr;
	typedef const ISemaphorePtr& ISemaphoreRef;

	// {df043049-1d54-4a3e-99fd-8184561cf9da} 
	MC_DEFINE_GUID(IID_ISemaphore, 
	0xdf043049, 0x1d54, 0x4a3e, 0x99, 0xfd, 0x81, 0x84, 0x56, 0x1c, 0xf9, 0xda);

	ISemaphorePtr InstantiateSemaphore();

}

#endif // !ISEMAPHORE_H__MINCOM__COMMONKIT__INCLUDED_
