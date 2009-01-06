#ifndef ILOG_H__MINCOM__COMMONKIT__INCLUDED_
#define ILOG_H__MINCOM__COMMONKIT__INCLUDED_

namespace MinCOM
{

	interface ILog : public ICommon
	{

		virtual result Notify(const String& message) = 0;

	};

	typedef ComPtr< ILog > ILogPtr;
	typedef const ILogPtr& ILogRef;

	// {e56bc469-a242-447e-9715-2c41a436647f} 
	MC_DEFINE_GUID(IID_ILog, 
	0xe56bc469, 0xa242, 0x447e, 0x97, 0x15, 0x2c, 0x41, 0xa4, 0x36, 0x64, 0x7f);

	// {1fc9bd35-f713-47d6-8fb3-e5df96a8b175} 
	MC_DEFINE_GUID(CLSID_DefaultLog, 
	0x1fc9bd35, 0xf713, 0x47d6, 0x8f, 0xb3, 0xe5, 0xdf, 0x96, 0xa8, 0xb1, 0x75);

	ILogPtr InstantiateLog();

#ifdef INTRENAL_LOG

	#define NOTIFY(x) mc::InstantiateLog()->Notify(x);

#else

	#define NOTIFY(x)

#endif

}

#endif // !ILOG_H__MINCOM__COMMONKIT__INCLUDED_
