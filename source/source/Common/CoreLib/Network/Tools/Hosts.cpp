#include "Common/Common.h"

#include "Network/Hosts/Localhost.h"

namespace Network
{

	IHostPtr InstantiateLocalhost()
	{
		return IHostPtr(mc::ObjectCreator< Localhost >(), IID_IHost);
	}

}
