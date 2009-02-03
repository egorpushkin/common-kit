#include "Common/Common.h"

#include "Commands/Commands.h"
#include "Commands/CommandEventsStub.h"

namespace MinCOM
{

	/**
	 * Definition for convenient access.
	 */
	typedef Loki::SingletonHolder< FactoryHolder, Loki::CreateUsingNew, Loki::DeletableSingleton > LocalFactoryHolder;

	FactoryHolder::FactoryHolder()
		: CommonHolder< FactoryImpl >()
	{
		IFactoryPtr factory(CommonHolder< FactoryImpl >::GetContained());

		// Register default translating stub.
		factory->Register( TypeInfo< ICommon >::GetGuid(), Class< CommonImpl< ICommon > >::Create );
	
		// Register commands engine stub.
		factory->Register( TypeInfo< ICommandEvents >::GetGuid(), Class< CommandEventsStub >::Create );
		factory->Register( TypeInfo< Commands >::GetGuid(), Class< Commands >::Create );



	}

	IFactoryPtr FactoryHolder::Instance()
	{
		return LocalFactoryHolder::Instance().GetContained();
	}

}

