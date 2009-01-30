#ifndef ISYNCHROHANDLE_H__MINCOM__COMMONKIT__INCLUDED_
#define ISYNCHROHANDLE_H__MINCOM__COMMONKIT__INCLUDED_

namespace MinCOM
{

	interface ISynchroHandle : public ICommon
	{

		virtual result GetHandle(handle* pHandle) = 0;

	};

	typedef ComPtr< ISynchroHandle > ISynchroHandlePtr;
	typedef ComPtr< ISynchroHandle, false > ISynchroHandleWeak;

	typedef const ISynchroHandlePtr& ISynchroHandleRef;
	typedef const ISynchroHandleWeak& ISynchroHandleWeakRef;

	// {53fe5bf3-9592-4492-aac4-9a35f00bd506} 
	MC_DEFINE_GUID(IID_ISynchroHandle, 
	0x53fe5bf3, 0x9592, 0x4492, 0xaa, 0xc4, 0x9a, 0x35, 0xf0, 0x0b, 0xd5, 0x06);

}

#endif // !ISYNCHROHANDLE_H__MINCOM__COMMONKIT__INCLUDED_
