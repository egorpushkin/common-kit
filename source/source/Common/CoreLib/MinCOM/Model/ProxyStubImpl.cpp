#include "Common/Common.h"

namespace MinCOM
{

	ProxyStubImpl::ProxyStubImpl()
		: mode_(PS_UNDEFINED)
		, proxyTarget_()
		, stubTarget_()
	{
	}

	// ICommon section
	BEGIN_INTERFACE_MAP(ProxyStubImpl)
		COMMON(IProxyStub)
		INTERFACE(IProxyStub)
	END_INTERFACE_MAP()

	// IProxyStub section
	result ProxyStubImpl::SetProxyTarget(IAgentRef proxyTarget)
	{
		if ( PS_UNDEFINED != mode_ )
			return _E_FAIL;
		
		proxyTarget_ = proxyTarget;
		mode_ = PS_PROXY;

		return _S_OK;
	}

	result ProxyStubImpl::SetStubTarget(ICommonRef stubTarget)
	{
		if ( PS_UNDEFINED != mode_ )
			return _E_FAIL;

		stubTarget_ = stubTarget;
		mode_ = PS_STUB;

		return _S_OK;
	}

	// ICommon section
	DECLARE_INTERFACE_MAP()		

	// Protected tools
	IAgentPtr ProxyStubImpl::GetProxyTarget() const
	{
		return proxyTarget_;
	}

	ICommonPtr ProxyStubImpl::GetStubTarget() const
	{
		return stubTarget_;
	}	

	PSState ProxyStubImpl::GetMode()
	{
		return mode_;
	}

}
