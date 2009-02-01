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

class Test 
	: public mc::CommonImpl< ICommandEvents >
{
public:

	// ICommandEvents section
	virtual result ModifiedChanged(bool modified)
	{

	
		return _S_OK;
	}


protected:
private:
};

bool Test4()
{
	// 
/*	mc::Strong< mc::ICommon > ptr1( mc::Class< Test >::Create() );
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
	if ( weak2 != NULL ) {} */

	mc::ICommandsPtr commands();



	return true;
}
