/*
 * File name   : Test1.cpp
 *
 * Copyright (c) 2008 Scientific Software
 *
 * Modification History:
 * Date        Name                Description
 * 2009-01-09  Egor Pushkin        Initial version
 */

#include "stdafx.h"

bool Test1()
{
	//
	mc::Strong< ITest1 > ptr1;
	assert( NULL == ptr1 );

	// 
	mc::Strong< ITest1 > ptr2(NULL);	
	assert( NULL == ptr1 );

	// 
	mc::Strong< ITest1 > ptr3 = NULL;	
	assert( NULL == ptr1 );

	// 
	mc::Strong< ITest1 > ptr4( (ITest1*)123 );	
	assert( NULL == ptr1 );

	return true;
}
