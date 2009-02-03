/*
 * File name   : Test2.cpp
 *
 * Copyright (c) 2008 Scientific Software
 *
 * Modification History:
 * Date        Name                Description
 * 2009-01-09  Egor Pushkin        Initial version
 */

#include "stdafx.h"

bool Test2()
{
	//
	mc::Strong< mc::ICommon > ptr1( mc::Class< Test >::Create() );
	assert( NULL != ptr1 );

	// 
	mc::Strong< mc::ICommon > ptr2 = mc::Class< Test >::Create();
	assert( NULL != ptr2 );

	// 
	mc::Strong< mc::ICommon > ptr3( mc::Class< Test >::Create() );
	assert( NULL != ptr3 );
	ptr3 = NULL;
	assert( NULL == ptr3 );

	// 
	mc::Strong< mc::ICommon > ptr4 = mc::Class< Test >::Create();
	assert( NULL != ptr2 );
	if ( ptr4 ) {}
	if ( !ptr4 ) {}
	if ( NULL != ptr4 ) {}
	if ( NULL == ptr4 ) {}
	if ( ptr4 == NULL ) {}
	if ( ptr4 != NULL ) {}

	return true;
}
