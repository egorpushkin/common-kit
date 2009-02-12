#include "Common/Common.h"

#include "Commands/Commands.h"
#include "Container/Vector.h"
#include "Container/List.h"
#include "Concurrency/Core/Event.h"
#include "Concurrency/Core/Mutex.h"
#include "Concurrency/Core/Semaphore.h"
#include "Concurrency/Core/Thread.h"
#include "Concurrency/Jobs/JobsQueue.h"
#include "Network/Core/Service.h"
#include "Network/Core/TCPConnection.h"

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

	// Events
	//////////////////////////////////////////////////////////////////////////

/*	IEventPtr Library::Event(bool manualReset /* = true *, bool initialState /* = false *, const std::string& name /* = std::string() *)
	{
		return Class< mc::Event >::Create(manualReset, initialState, name);
	}

	IEventPtr Library::EventOpen(const std::string& name)
	{
		return Class< mc::Event >::Create(name);
	} */

	// Mutexes
	//////////////////////////////////////////////////////////////////////////

	IMutexPtr Library::Mutex(bool obtain /* = false */, const std::string& name /* = std::string() */)
	{
		return Class< mc::Mutex >::Create(obtain, name);
	}

	IMutexPtr Library::MutexOpen(const std::string& name)
	{
		return Class< mc::Mutex >::Create(name);
	}

	// Semaphores
    //////////////////////////////////////////////////////////////////////////
    
	ISemaphorePtr Library::Semaphore(long initial, long maximum, const std::string& name /* = std::string() */)
	{
		return Class< mc::Semaphore >::Create(initial, maximum, name);
	}

	ISemaphorePtr Library::SemaphoreOpen(const std::string& name)
	{
		return Class< mc::Semaphore >::Create(name);
	}

	IThreadPtr Library::Thread()
	{
		return Class< mc::Thread >::Create();
	}

	IServicePtr Library::Service()
	{
		return Class< mc::Service >::Create(); 
	}

	IJobsQueuePtr Library::JobsQueue()
	{
		return Class< mc::JobsQueue >::Create();
	}
	
	IConnectionPtr Library::TCPConnection(IServiceRef service)
	{
		return Class< mc::TCPConnection >::Create(service);
	}

	IFactoryPtr Library::Factory()
	{
		return Class< mc::FactoryImpl >::Create();
	}

}
