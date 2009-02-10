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

class TestEvent 
	: public mc::CommonImpl< mc::DCommands >
{
public:

	// ICommandEvents section
	virtual mc::result ModifiedChanged(bool /* modified */)
	{
		std::cout << "Test->ModifiedChanged" << std::endl;	
		return mc::_S_OK;
	}

};
 
bool Test4()
{
	
	{
		// Construct commands container.
		mc::ICommandsPtr commands( mc::Library::Commands() );
		// Construct events listener.
		mc::ICommonPtr eventsListener( mc::Class< TestEvent >::Create() );
		// Subscribe on events.
		mc::Events::Advise(commands, eventsListener, mc::TypeInfo< mc::DCommands >::GetGuid() );	

		
		commands->SetModified(true);

 		Loki::DeletableSingleton< mc::FactoryHolder >::GracefulDelete();
	}


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

	return true;
}
