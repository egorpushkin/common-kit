#include "Common/Common.h"

#include "Localhost.h"

namespace Network
{

	namespace Private
	{

		const mc::StringA localhost("localhost");

	}

	Localhost::Localhost()
		: HostImpl(Private::localhost, true)
	{
	}

	Localhost::Localhost(const mc::StringA& port)
		: HostImpl(Private::localhost, port)
	{
	}

}
