#include "Common/Common.h"

#include "Commands/Commands.h"
#include "Network/Source/Service.h"
#include "Container/Vector.h"

namespace MinCOM
{

	// {B6797FE8-F11D-423c-ADD5-5A8D35D09316}
	const Guid TypeInfo< Commands >::iid_ = 
		{ 0xb6797fe8, 0xf11d, 0x423c, 0xad, 0xd5, 0x5a, 0x8d, 0x35, 0xd0, 0x93, 0x16 };

	// {A68A0C30-DDAF-42af-96AF-BDDEA8AA4DBC}
	const Guid TypeInfo< Service >::iid_ = 
		{ 0xa68a0c30, 0xddaf, 0x42af, 0x96, 0xaf, 0xbd, 0xde, 0xa8, 0xaa, 0x4d, 0xbc };

	// {EAB73CC1-3B5D-4deb-BBA7-FFE15D295734}
	const Guid TypeInfo< Vector::IPrivateIterator_ >::iid_ = 
	{ 0xeab73cc1, 0x3b5d, 0x4deb, 0xbb, 0xa7, 0xff, 0xe1, 0x5d, 0x29, 0x57, 0x34 };

}
