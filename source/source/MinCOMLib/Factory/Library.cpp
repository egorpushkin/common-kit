#include "Common/Common.h"

#include "Commands/Commands.h"
#include "Container/Vector.h"
#include "Container/List.h"
#include "Concurrency/Event.h"
#include "Concurrency/Mutex.h"
#include "Concurrency/Thread.h"
#include "Network/Source/Service.h"
#include "Network/Source/TCPConnection.h"

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

	IThreadPtr Library::Thread()
	{
		return Class< mc::Thread >::Create();
	}

	IServicePtr Library::Service()
	{
		return Class< mc::Service >::Create(); 
	}
	
	IConnectionPtr Library::TCPConnection(IServiceRef service)
	{
		return Class< mc::TCPConnection >::Create(service);
	}

}
