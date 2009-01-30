#ifndef IMUTEX_H__MINCOM__COMMONKIT__INCLUDED_
#define IMUTEX_H__MINCOM__COMMONKIT__INCLUDED_

namespace MinCOM
{

	interface IMutex : public ISynchro
	{

		virtual result Enter(unsigned long milliseconds = _INFINITE) = 0;

		virtual result Leave() = 0;

	};

	typedef ComPtr< IMutex > IMutexPtr;
	typedef ComPtr< IMutex, false > IMutexWeak;

	typedef const IMutexPtr& IMutexRef;
	typedef const IMutexWeak& IMutexWeakRef;

	// {e615e39d-191f-4ab1-8c2d-2385a05d79e3} 
	MC_DEFINE_GUID(IID_IMutex, 
	0xe615e39d, 0x191f, 0x4ab1, 0x8c, 0x2d, 0x23, 0x85, 0xa0, 0x5d, 0x79, 0xe3);

	// {1d82254a-8863-4f03-b751-1cdd309bda9d} 
	MC_DEFINE_GUID(CLSID_Mutex, 
	0x1d82254a, 0x8863, 0x4f03, 0xb7, 0x51, 0x1c, 0xdd, 0x30, 0x9b, 0xda, 0x9d);

	// {104cd5d0-dac7-4f28-af96-2cce6040214f} 
	MC_DEFINE_GUID(CLSID_CritSect, 
	0x104cd5d0, 0xdac7, 0x4f28, 0xaf, 0x96, 0x2c, 0xce, 0x60, 0x40, 0x21, 0x4f);

	IMutexPtr InstantiateMutex();

}

#endif // !IMUTEX_H__MINCOM__COMMONKIT__INCLUDED_
