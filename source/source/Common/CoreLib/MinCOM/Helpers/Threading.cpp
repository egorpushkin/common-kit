#include "Common/Common.h"

#include "MinCOM/Threading/Event.h"

#include "MinCOM/Threading/Mutex.h"

#include "MinCOM/Threading/Semaphore.h"

#include "MinCOM/Threading/Thread.h"

#include "MinCOM/Threading/MultiSynchro.h"

namespace MinCOM
{
	
	EventLock::EventLock(IEventRef event)
		: synchro_(ISynchroPtr(event, IID_ISynchro))
	{
		if ( synchro_ )
			synchro_->Wait();
	}

	EventLock::~EventLock()
	{
		if ( synchro_ )
			synchro_->Reset();
	}

	MutexLock::MutexLock(IMutexRef mutex)
		: mutex_(mutex)
	{
		if ( mutex_ )
			mutex_->Enter();
	}

	MutexLock::~MutexLock()
	{
		if ( mutex_ )
			mutex_->Leave();
	}

	IEventPtr InstantiateEvent()
	{
		return IEventPtr(ObjectCreator< Event >(), IID_IEvent);
	}

	IMutexPtr InstantiateMutex()
	{
		return IMutexPtr(ObjectCreator< Mutex >(), IID_IMutex);
	}

	ISemaphorePtr InstantiateSemaphore()
	{
		return ISemaphorePtr(ObjectCreator< Semaphore >(), IID_ISemaphore);
	}

	IThreadPtr InstantiateThread()
	{
		return IThreadPtr(ObjectCreator< Thread >(), IID_IThread);
	}

	IMultiSynchroPtr InstantiateMultiSynchro()
	{
		return IMultiSynchroPtr(ObjectCreator< MultiSynchro >(), IID_IMultiSynchro);
	}

}
