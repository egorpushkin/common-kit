#include "Common/Common.h"

#include "Service.h"

namespace Network
{

	asio::io_service& Service::service()
	{
		return service_;
	}

	asio::io_service& service()
	{
		return ServiceHolder::Instance().service();
	}

}
