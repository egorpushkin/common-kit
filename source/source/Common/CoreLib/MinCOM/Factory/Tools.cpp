#include "Common/Common.h"

namespace MinCOM
{

	namespace Private
	{

		Strong<ICommon> ObjectCreatorInternal(const Strong<ICommon> & common)
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
