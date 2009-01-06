#include "Common/Common.h"

namespace MinCOM
{

	namespace Private
	{

		ICommon::Ptr_ ObjectCreatorInternal(ICommon::Ref_ common)
		{
			/* IItemPtr objectItem(common, IID_IItem);
			if ( objectItem )
			{
				objectItem->SetLocal(common);
				objectItem->PostInit();
			} */

			return common;
		}	

	}

}
