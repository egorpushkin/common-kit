#include "Common/Common.h"

namespace MinCOM
{

	result Events::Advise(ICommonRef connectee, ICommonRef connector, unsigned long& cookie, RefIid apIid)
	{
		IAccessProviderPtr accessProvider(connectee);
		if ( !accessProvider || !connector )
			return _E_INVALIDARG;

		IAccessPointPtr accessPoint( accessProvider->Find(apIid) );
		if ( !accessPoint )
			return _E_FAIL;

		return accessPoint->Advise(connector, cookie);
	}

	result Events::Unadvise(ICommonRef connectee, unsigned long cookie, RefIid apIid)
	{
		mc::IAccessProviderPtr accessProvider(connectee);
		if ( !accessProvider )
			return _E_FAIL;

		mc::IAccessPointPtr accessPoint( accessProvider->Find(apIid) );
		if ( !accessPoint )
			return _E_FAIL;

		return accessPoint->Unadvise(cookie);
	}

}
