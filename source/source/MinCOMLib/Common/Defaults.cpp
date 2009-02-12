#include "Common/Common.h"

#include "Commands/Commands.h"

namespace MinCOM
{

    template<> const Guid Class< ICommands >::clsid_ = TypeInfo< Commands >::GetGuid();

}
