#include "Common/Common.h"

namespace MinCOM
{

	/**
	 * MinCOM provides default implementation of a tool for
	 * instantiating objects (by Clsid) which are not declared in 
	 * the scope of client source code (for example, objects from 
	 * shared libraries).
	 *
	 * This implementation checks whether object can be found locally 
	 * and then attempts to find it in shared library. NULL reference
	 * is returned to caller if both attempts fail.
	 */
	Strong<ICommon> Object::Create(RefClsid clsid)
	{
		// Try to instantiate object from local registry.
		ICommonPtr objectStep1 = FactoryHolder::Instance()->Create(clsid);
		if ( objectStep1 )
			return objectStep1;

		// Try to instantiate object from shared component.
		// TODO
		return NULL;
	}

	ICommonPtr Object::CreateStub(RefIid clsid, ICommonRef target, bool strong)
	{
		ICommonPtr stub( Object::Create(clsid) );
		if ( !stub )
			return NULL;
		stub->SetTarget(target, strong);
		return stub;		
	}


}
