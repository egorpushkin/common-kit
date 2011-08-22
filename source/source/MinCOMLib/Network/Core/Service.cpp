#include "Common/Common.h"

#include "Service.h"

namespace MinCOM
{

	Service::Service()
		: CommonImpl< IService >()
		, service_()
	{
	}

	// IService section
	void Service::Run()
	{
		service_.reset();
		service_.run();
	}

	void Service::Stop()
	{
		service_.stop();
	}

	boost::asio::io_service& Service::GetService()
	{
		return service_;
	}

}
