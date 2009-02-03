#include "Common/Common.h"

#include "Commands/Commands.h"
#include "Container/Vector.h"
#include "Container/List.h"
#include "Concurrency/Event.h"
#include "Concurrency/Mutex.h"

namespace MinCOM
{

	ICommandsPtr Library::Commands()
	{
		return Class< mc::Commands >::Create();
	}

	IVectorPtr Library::Vector()
	{
		return Class< mc::Vector >::Create();
	}

	IListPtr Library::List()
	{
		return Class< mc::List >::Create();
	}

	IEventPtr Library::Event()
	{
		return Class< mc::Event >::Create();
	}

	IMutexPtr Library::Mutex()
	{
		return Class< mc::Mutex >::Create();
	}


}
