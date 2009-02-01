/*
 * File name   : Test3.cpp
 *
 * Copyright (c) 2008 Scientific Software
 *
 * Modification History:
 * Date        Name                Description
 * 2009-01-22  Egor Pushkin        Initial version
 */

#include "stdafx.h"

bool Test3()
{
	// 
	mc::Strong< mc::ICommon > ptr1( mc::Class< Test >::Create() );
	assert( NULL != ptr1 );

	mc::Strong< ITest1 > test1( ptr1 );
	assert( NULL != test1 );

	test1->DoStuff1();
	
	// 
	mc::Strong< mc::ICommon > ptr2( mc::Class< Test >::Create() );
	assert( NULL != ptr2 );

	mc::Strong< ITest1 > test2( ptr2 );
	assert( NULL != test2 );

	test2->DoStuff1();

	test2 = NULL;
	assert( NULL == test2 );

	// 



	return true;
}
