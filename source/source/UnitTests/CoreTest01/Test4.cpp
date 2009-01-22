/*
 * File name   : Test4.cpp
 *
 * Copyright (c) 2008 Scientific Software
 *
 * Modification History:
 * Date        Name                Description
 * 2009-01-22  Egor Pushkin        Initial version
 */

#include "stdafx.h"

bool Test4()
{
	// 
	mc::Strong< mc::ICommon > ptr1( mc::ObjectCreator< Test >() );
	assert( NULL != ptr1 );
	
	mc::Weak< mc::ICommon > weak1;

	mc::Weak< mc::ICommon > weak2( ptr1 );

	weak2 = ptr1;

	ptr1 = NULL;
	
	if ( weak2 ) {}
	if ( !weak2 ) {}
	if ( NULL != weak2 ) {}
	if ( NULL == weak2 ) {}
	if ( weak2 == NULL ) {}
	if ( weak2 != NULL ) {}



	return true;
}
