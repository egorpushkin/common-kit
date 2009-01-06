#include "Common/Common.h"

#include "PointPS.h"

namespace Areas
{

	PointPS::PointPS()
		: mc::CommonImpl< Areas::IPoint >()
		, mc::AgentImpl()
		, mc::ProxyStubImpl()
		, Components::ObjCounter()
	{
	}

	// ICommon section
	BEGIN_INTERFACE_MAP(PointPS)
		COMMON(IPoint)
		INTERFACE(IPoint)
		IMPL(mc::AgentImpl)
		IMPL(mc::ProxyStubImpl)
	END_INTERFACE_MAP()

	// IPoint section
	void PointPS::SetLocation(double x, double y)
	{
		mc::IAgentPtr proxyTarget = mc::ProxyStubImpl::GetProxyTarget();
		if ( !proxyTarget )
			return;

		proxyTarget->Invoke(
			AGENTID_PT_SETLOCATION,
			mc::CreateParams(x, y),
			NULL,
			IID_IPoint);
	}

	void PointPS::SetX(double x)
	{
		SetLocation(x, GetY());
	}

	void PointPS::SetY(double y)
	{
		SetLocation(GetX(), y);
	}

	double PointPS::GetX() const
	{
		mc::IAgentPtr proxyTarget = mc::ProxyStubImpl::GetProxyTarget();
		if ( !proxyTarget )
			return 0.0;

		mc::IVariantWrapperRef result = mc::ConstructVariantWrapper();
		
		proxyTarget->Invoke(
			AGENTID_PT_GETX,
			NULL,
			result,
			IID_IPoint);

		return result->GetData().toDouble();
	}

	double PointPS::GetY() const
	{
		mc::IAgentPtr proxyTarget = mc::ProxyStubImpl::GetProxyTarget();
		if ( !proxyTarget )
			return 0.0;

		mc::IVariantWrapperRef result = mc::ConstructVariantWrapper();

		proxyTarget->Invoke(
			AGENTID_PT_GETY,
			NULL,
			result,
			IID_IPoint);

		return result->GetData().toDouble();
	}

	// IAgent section
	mc::result PointPS::Invoke(mc::DispId idMember, mc::DispParamsRef dispParams, mc::IVariantWrapperRef result, mc::RefIid /* iid */)
	{
		IPointPtr stubTarget(mc::ProxyStubImpl::GetStubTarget(), IID_IPoint);
		if ( !stubTarget )
			return mc::_E_FAIL;

		if ( AGENTID_PT_SETLOCATION == idMember )
		{
			if ( !dispParams->Get(0) || !dispParams->Get(1) )
				return mc::_E_FAIL;

			stubTarget->SetLocation(
				dispParams->Get(1)->toDouble(),
				dispParams->Get(0)->toDouble());
		}
		else if ( AGENTID_PT_GETX == idMember )
		{
			if ( !result )
				return mc::_E_FAIL;

			result->SetData(stubTarget->GetX());
		}
		else if ( AGENTID_PT_GETY == idMember )
		{
			if ( !result )
				return mc::_E_FAIL;

			result->SetData(stubTarget->GetY());
		}
		else
			return mc::_E_NOTIMPL;

		return mc::_S_OK;
	}

}
