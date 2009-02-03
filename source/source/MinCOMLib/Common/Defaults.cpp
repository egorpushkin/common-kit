#include "Common/Common.h"

#include "Commands/Commands.h"

namespace MinCOM
{

	const Guid Class< ICommands >::clsid_ = TypeInfo< Commands >::GetGuid();

}
