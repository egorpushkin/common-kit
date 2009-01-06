#ifndef ISYNCHRO_H__MINCOM__COMMONKIT__INCLUDED_
#define ISYNCHRO_H__MINCOM__COMMONKIT__INCLUDED_

namespace MinCOM
{

	typedef enum tagWaitDelay
	{

		_INFINITE = 0xFFFFFFFF

	} tagWaitDelay;

	interface ISynchro : public ICommon
	{

		virtual result Wait(unsigned long milliseconds = _INFINITE) = 0;

		virtual result Signal() = 0;

		virtual result Reset() = 0;

	};

	typedef ComPtr< ISynchro > ISynchroPtr;
	typedef ComPtr< ISynchro, false > ISynchroWeak;

	typedef const ISynchroPtr& ISynchroRef;
	typedef const ISynchroWeak& ISynchroWeakRef;

	// {2d5835d5-54f9-4063-a2b6-935b16d631b2} 
	MC_DEFINE_GUID(IID_ISynchro, 
	0x2d5835d5, 0x54f9, 0x4063, 0xa2, 0xb6, 0x93, 0x5b, 0x16, 0xd6, 0x31, 0xb2);

}

#endif // !ISYNCHRO_H__MINCOM__COMMONKIT__INCLUDED_
