#include "Common/Common.h"

#include "Commands/Commands.h"
#include "Commands/DCommandsStub.h"
#include "Network/Core/DRawDataStub.h"
#include "Network/Core/DServerStub.h"
#include "Network/Protocol/DProtocolStub.h"

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
		factory->Register( TypeInfo< DCommands >::GetGuid(), Class< DCommandsStub >::Create );

		// Register network engine stubs.
		factory->Register( TypeInfo< DRawData >::GetGuid(), Class< DRawDataStub >::Create );
		factory->Register( TypeInfo< DServer >::GetGuid(), Class< DServerStub >::Create );
		factory->Register( TypeInfo< DProtocol >::GetGuid(), Class< DProtocolStub >::Create );

	}

	IFactoryPtr FactoryHolder::Instance()
	{
		return LocalFactoryHolder::Instance().GetContained();
	}

}

