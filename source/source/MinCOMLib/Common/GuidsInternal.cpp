#include "Common/Common.h"

#include "Commands/Commands.h"
#include "Network/Core/Service.h"
#include "Container/Vector.h"

namespace MinCOM
{

	// {B6797FE8-F11D-423c-ADD5-5A8D35D09316}
    template<> const Guid TypeInfo< Commands >::iid_ = 
		{ 0xb6797fe8, 0xf11d, 0x423c, 0xad, 0xd5, 0x5a, 0x8d, 0x35, 0xd0, 0x93, 0x16 };

	// {A68A0C30-DDAF-42af-96AF-BDDEA8AA4DBC}
    template<> const Guid TypeInfo< Service >::iid_ = 
		{ 0xa68a0c30, 0xddaf, 0x42af, 0x96, 0xaf, 0xbd, 0xde, 0xa8, 0xaa, 0x4d, 0xbc };

}
