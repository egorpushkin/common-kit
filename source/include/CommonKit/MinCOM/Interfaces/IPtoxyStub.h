#ifndef IPROXYSTUB_H__MINCOM__COMMONKIT__INCLUDED_
#define IPROXYSTUB_H__MINCOM__COMMONKIT__INCLUDED_

namespace MinCOM
{

	interface IProxyStub : public ICommon
	{

		virtual result SetProxyTarget(IAgentRef proxyTarget) = 0;

		virtual result SetStubTarget(ICommonRef stubTarget) = 0;

	};

	typedef ComPtr< IProxyStub > IProxyStubPtr;
	typedef const IProxyStubPtr& IProxyStubRef;

	// {4DE02019-538B-44b7-B4EF-23905607C56A}
	MC_DEFINE_GUID(IID_IProxyStub, 
	0x4de02019, 0x538b, 0x44b7, 0xb4, 0xef, 0x23, 0x90, 0x56, 0x7, 0xc5, 0x6a);

	// Thread events
	typedef enum tagPSState
	{

		PS_UNDEFINED = 0x0,
	
		PS_PROXY = 0x1,

		PS_STUB

	} PSState;

}

#endif // !IPROXYSTUB_H__MINCOM__COMMONKIT__INCLUDED_
