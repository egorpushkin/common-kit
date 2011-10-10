#include "Common/Common.h"

#include "Service.h"
#include "NetworkStats.h"

namespace MinCOM
{

	Service::Service()
		: CommonImpl< IService >()
		, service_()
		, stats_( mc::Class< NetworkStats >::Create() )
	{
	}

	// IService section
	void Service::Run()
	{
		stats_->StartSession();
		service_.reset();
		service_.run();
	}

	void Service::Stop()
	{
		service_.stop();
	}
	
	INetworkStatsPtr Service::GetStats() const
	{
		return stats_;
	}	

	boost::asio::io_service& Service::GetService()
	{
		return service_;
	}
	
}
