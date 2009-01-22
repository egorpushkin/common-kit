#include "stdafx.h"

#ifdef _MSC_VER 
#include <crtdbg.h>
#endif // _MSC_VER

bool Test1();
bool Test2();
bool Test3();
bool Test4();

int _tmain(int /* argc */, _TCHAR* /* argv[] */)
{
	Test1();
	Test2();
	Test3();
	Test4();

#ifdef _MSC_VER 
	_CrtDumpMemoryLeaks(); 
#endif // _MSC_VER

	return 0;
}
