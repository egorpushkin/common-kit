#include "Common/Common.h"

#include "EventsSpreader.h"

namespace MinCOM
{

	EventsSpreader::EventsSpreader(IAccessProviderRef accessProvider)
		: accessProvider_(accessProvider)
	{
	}

	// ICommon section
	result EventsSpreader::Invoke(const Call& call)
	{
		// Reconstruct pointer.
		IAccessProviderPtr accessProvider(accessProvider_);
		if ( !accessProvider )
			return _E_NOTINIT;
		// Spread event.
		return accessProvider->Spread(call);
	}

}
