#include "Common/Common.h"

namespace Network
{

	namespace Private
	{

		const mc::StringA defaultPort("5678");

	}

	HostImpl::HostImpl()
		: mc::CommonImpl< IHost >()
		, host_()
		, port_()
	{
	}

	HostImpl::HostImpl(const mc::StringA& host, bool defaultPort)
		: mc::CommonImpl< IHost >()
		, host_(host)
		, port_()
	{
		if ( defaultPort )
			port_ = Private::defaultPort;
	}

	HostImpl::HostImpl(const mc::StringA& host, const mc::StringA& port)
		: mc::CommonImpl< IHost >()
		, host_(host)
		, port_(port)
	{
	}

	// ICommon section
	BEGIN_INTERFACE_MAP(HostImpl)
		COMMON(IHost)
		INTERFACE(IHost)
	END_INTERFACE_MAP()

	// IHost section
	mc::StringA HostImpl::GetHost()
	{
		return host_;
	}

	mc::StringA HostImpl::GetPort()
	{
		return port_;
	}

}
