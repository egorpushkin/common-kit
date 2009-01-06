#ifndef IEVENT_H__MINCOM__COMMONKIT__INCLUDED_
#define IEVENT_H__MINCOM__COMMONKIT__INCLUDED_

namespace MinCOM
{

	interface IEvent : public ISynchro
	{

		virtual result Pulse() = 0;

	};

	typedef ComPtr< IEvent > IEventPtr;
	typedef ComPtr< IEvent, false > IEventWeak;

	typedef const IEventPtr& IEventRef;
	typedef const IEventWeak& IEventWeakRef;

	// {e137a6ce-1daa-4e7f-b157-eb9be83d3256} 
	MC_DEFINE_GUID(IID_IEvent, 
	0xe137a6ce, 0x1daa, 0x4e7f, 0xb1, 0x57, 0xeb, 0x9b, 0xe8, 0x3d, 0x32, 0x56);

	// {84d46598-4ed7-4e04-a0fa-4272ae87faa8} 
	MC_DEFINE_GUID(CLSID_Event, 
	0x84d46598, 0x4ed7, 0x4e04, 0xa0, 0xfa, 0x42, 0x72, 0xae, 0x87, 0xfa, 0xa8);

	IEventPtr InstantiateEvent();

}

#endif // !IEVENT_H__MINCOM__COMMONKIT__INCLUDED_
