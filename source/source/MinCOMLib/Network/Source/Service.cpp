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
		service_.run();
	}

	void Service::Stop()
	{
		service_.stop();
	}

	void Service::Work()
	{
		boost::asio::io_service::work work(service_);
	}

	boost::asio::io_service& Service::GetService()
	{
		return service_;
	}

}
