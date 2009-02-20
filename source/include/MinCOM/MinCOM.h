#ifndef MINCOM_H__MINCOM__COMMONKIT__INCLUDED_
#define MINCOM_H__MINCOM__COMMONKIT__INCLUDED_

// External requirements
//////////////////////////////////////////////////////////////////////////
#include "MinCOM/External.h"

// MinCOM namespace declaration
//////////////////////////////////////////////////////////////////////////
namespace MinCOM {}
namespace mc = MinCOM;

// Most common declarations
//////////////////////////////////////////////////////////////////////////
#include "MinCOM/Common/Errors.h"
#include "MinCOM/Common/Guid.h"
#include "MinCOM/Common/Common.h"
#include "MinCOM/Common/ToolsMap.h"
#include "MinCOM/Common/MethodWrapper.h"

// Core concurrency
//////////////////////////////////////////////////////////////////////////
#include "MinCOM/Concurrency/Core/CoreMutex.h"
#include "MinCOM/Concurrency/Core/CoreCounter.h"

// Smart pointers
//////////////////////////////////////////////////////////////////////////
#include "MinCOM/Pointers/DualRefCounter.h"
#include "MinCOM/Pointers/Strong.h"
#include "MinCOM/Pointers/Weak.h"
#include "MinCOM/Pointers/BinaryOperators.h"
#include "MinCOM/Pointers/StdExtensions.h"

// Core object model support
//////////////////////////////////////////////////////////////////////////
#include "MinCOM/Common/Call.h"
#include "MinCOM/Common/ICommon.h"
#include "MinCOM/Common/CommonImpl.h"
#include "MinCOM/Common/Class.h"
#include "MinCOM/Common/Object.h"

// Container component
//////////////////////////////////////////////////////////////////////////
#include "MinCOM/Container/Interfaces/IEnumerator.h"
#include "MinCOM/Container/Interfaces/IVector.h"
#include "MinCOM/Container/Interfaces/IList.h"
#include "MinCOM/Container/Interfaces/IMap.h"
#include "MinCOM/Container/Interfaces/DContainer.h"

// Variant support for dispatching
//////////////////////////////////////////////////////////////////////////
#include "MinCOM/Variant/CommonVariant.h"
#include "MinCOM/Variant/WrapperT.h"

// Events dispatching, marshaling 
//////////////////////////////////////////////////////////////////////////
#include "MinCOM/Events/Interfaces/IAccessPoint.h"
#include "MinCOM/Events/Interfaces/IAccessProvider.h"
#include "MinCOM/Events/Interfaces/Events.h"
#include "MinCOM/Events/Impl/AccessPointImpl.h"
#include "MinCOM/Events/Impl/AccessProviderImpl.h"

// Commands engine
//////////////////////////////////////////////////////////////////////////
#include "MinCOM/Commands/ICommand.h"
#include "MinCOM/Commands/ICommands.h"
#include "MinCOM/Commands/DCommands.h"

// Basic support for concurrency
//////////////////////////////////////////////////////////////////////////
#include "MinCOM/Concurrency/Interfaces/ISynchro.h"
#include "MinCOM/Concurrency/Interfaces/IEvent.h"
#include "MinCOM/Concurrency/Interfaces/IMutex.h"
#include "MinCOM/Concurrency/Interfaces/ISemaphore.h"
#include "MinCOM/Concurrency/Interfaces/IRunnable.h"
#include "MinCOM/Concurrency/Interfaces/IThread.h"
#include "MinCOM/Concurrency/Interfaces/IJobsQueue.h"
#include "MinCOM/Concurrency/Interfaces/IReadWriteLock.h"

// Factory support
//////////////////////////////////////////////////////////////////////////
#include "MinCOM/Factory/IFactory.h"
#include "MinCOM/Factory/FactoryImpl.h"
#include "MinCOM/Factory/CommonHolder.h"
#include "MinCOM/Factory/FactoryHolder.h"

// Networking support
//////////////////////////////////////////////////////////////////////////
#include "MinCOM/Network/Core/IHost.h"
#include "MinCOM/Network/Core/IConnection.h"
#include "MinCOM/Network/Core/IServer.h"
#include "MinCOM/Network/Core/IService.h"
#include "MinCOM/Network/Core/DRawData.h"
#include "MinCOM/Network/Core/DServer.h"
#include "MinCOM/Network/Protocol/IMessage.h"
#include "MinCOM/Network/Protocol/IProtocol.h"
#include "MinCOM/Network/Protocol/DProtocol.h"
#include "MinCOM/Network/Protocol/MessageImpl.h"

// Local MinCOM registry of tools for fast and convenient access
#include "MinCOM/Factory/Library.h"

// Logging support
//////////////////////////////////////////////////////////////////////////
// #define INTRENAL_LOG
// #include "MinCOM/Interfaces/ILog.h"





#endif // !MINCOM_H__MINCOM__COMMONKIT__INCLUDED_
