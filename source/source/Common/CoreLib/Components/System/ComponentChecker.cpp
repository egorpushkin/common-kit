#include "Common/Common.h"

#include "CommonKit/Components.h"

#include "ComponentChecker.h"

namespace Components
{

	ComponentChecker::ComponentChecker(Method_ method)
		: method_(method)
	{
	}

	bool ComponentChecker::Check(IComponentRef component, mc::RefIid iid, mc::RefIid typeIid)
	{
		if ( method_ == METHOD_BYLIBTYPE_ )
		{
			if ( component->GetTypeIid() == typeIid && 
				component->CanProduce(iid) )
				return true;
		}
		else if ( method_ == METHOD_BYLIBIID_ )
		{
			if ( component->GetIid() == iid )
				return true;
		}
		else if ( method_ == METHOD_BYCLSID_ )
		{
			if ( component->CanProduce(iid) )
				return true;
		}

		return false;
	}

}