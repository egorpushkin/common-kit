#ifndef IMULTISYNCHRO_H__MINCOM__COMMONKIT__INCLUDED_
#define IMULTISYNCHRO_H__MINCOM__COMMONKIT__INCLUDED_

namespace MinCOM
{

	typedef enum tagWaitFlags 
	{

		WAIT_WAITALL          = 0x00000001,

		WAIT_ALERTABLE        = 0x00000002

	} WaitFlags;

	interface IMultiSynchro : public ICommon
	{

		virtual result Add(ISynchroRef synchro) = 0;

		virtual result Delete(ISynchroRef synchro) = 0;

		virtual result Wait(unsigned long milliseconds = _INFINITE, unsigned long flags = 0) = 0;

		virtual ISynchroPtr GetSignaled() = 0;

	};

	typedef ComPtr< IMultiSynchro > IMultiSynchroPtr;
	typedef ComPtr< IMultiSynchro, false > IMultiSynchroWeak;

	typedef const IMultiSynchroPtr& IMultiSynchroRef;
	typedef const IMultiSynchroWeak& IMultiSynchroWeakRef;

	// {23c1fb6a-82ce-4efb-ae3b-e5af80f9ad91} 
	MC_DEFINE_GUID(IID_IMultiSynchro, 
	0x23c1fb6a, 0x82ce, 0x4efb, 0xae, 0x3b, 0xe5, 0xaf, 0x80, 0xf9, 0xad, 0x91);
	
	IMultiSynchroPtr InstantiateMultiSynchro();

}

#endif // !IMULTISYNCHRO_H__MINCOM__COMMONKIT__INCLUDED_
