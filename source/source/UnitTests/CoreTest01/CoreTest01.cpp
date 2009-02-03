#include "stdafx.h"

#ifdef _MSC_VER 
#include <crtdbg.h>
#endif // _MSC_VER

bool Test1();
bool Test2();
bool Test3();
bool Test4();

// {2CC32701-BFC6-4ccf-B4B3-F5F28BD967E0}
const mc::Guid mc::TypeInfo< ITest1 >::iid_ = 
 	{ 0x2cc32701, 0xbfc6, 0x4ccf, 0xb4, 0xb3, 0xf5, 0xf2, 0x8b, 0xd9, 0x67, 0xe0 };

int _tmain(int /* argc */, _TCHAR* /* argv[] */)
{

	//size_t t = sizeof(mc::Variant);
	//std::cout << t << std::endl;

	Test1();
	Test2();
	Test3();
	Test4();

#ifdef _MSC_VER 
	_CrtDumpMemoryLeaks(); 
#endif // _MSC_VER

	return 0;
}
