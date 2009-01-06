#include "Common/Common.h"

#include "CommonKit/Network.h"

#include "Session.h"

namespace Network
{

	Session::Session(asio::io_service& io_service)
		: socket_(io_service)
	{
	}

	Session::Socket_& Session::socket()
	{
		return socket_;
	}

}
