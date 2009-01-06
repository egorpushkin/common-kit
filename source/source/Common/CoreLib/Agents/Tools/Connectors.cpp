#include "Common/Common.h"

namespace MinCOM
{

	mc::result Advise(
		ICommonRef connectee, 
		ICommonRef connector, 
		unsigned long& cookie, 
		RefIid apIid)
	{
		if ( !connectee || !connector )
			return mc::_E_INVALIDARG;

		mc::IAccessProviderPtr accessProvider(connectee, mc::IID_IAccessProvider);
		if ( !accessProvider )
			return _E_FAIL;

		mc::IAccessPointPtr accessPoint;
		mc::result code = accessProvider->FindAccessPoint(apIid, accessPoint);
		if ( mc::IsFailed(code) || !accessPoint )
			return _E_FAIL;

		return accessPoint->Advise(connector, cookie);
	}

	mc::result Unadvise(
		ICommonRef connectee, 
		unsigned long cookie, 
		RefIid apIid)
	{
		if ( !connectee )
			return mc::_E_INVALIDARG;

		mc::IAccessProviderPtr accessProvider(connectee, mc::IID_IAccessProvider);
		if ( !accessProvider )
			return _E_FAIL;

		mc::IAccessPointPtr accessPoint;
		mc::result code = accessProvider->FindAccessPoint(apIid, accessPoint);
		if ( mc::IsFailed(code) || !accessPoint )
			return _E_FAIL;

		return accessPoint->Unadvise(cookie);
	}

	mc::result Connect(
		ICommonRef connectee, 
		ICommonRef connector,
		RefIid apIid /* = IID_IAgent */)
	{
		// Set parent item for image member
		mc::IItemPtr connecteeItem(connectee, mc::IID_IItem);
		if ( connecteeItem )
			connecteeItem->SetParent(connector);

		// Subscribe on image events			
		unsigned long cookie = 0;
		return mc::Advise(connectee, connector, cookie, apIid);
	}

}
