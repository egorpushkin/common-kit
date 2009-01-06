// CoreTest02.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#ifdef _MSC_VER 
#include <crtdbg.h>
#endif // _MSC_VER

#include "CommonKit/MinCOM.h"

#include "CommonKit/Components.h"

#include "AreasKit/AreasKit.h"

#include <iostream>


int _tmain(int argc, _TCHAR* argv[])
{
	{

		mc::ICommonPtr cmnPoint = Components::InstantiateCommon(Areas::LIBID_Areas, Areas::CLSID_Point); 

		

		Areas::IPointPtr point(cmnPoint, Areas::IID_IPoint);
	



	}

#ifdef _MSC_VER 
	_CrtDumpMemoryLeaks(); 
#endif // _MSC_VER

	return 0;
}

