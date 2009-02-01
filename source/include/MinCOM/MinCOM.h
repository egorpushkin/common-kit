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

// Core concurrency
//////////////////////////////////////////////////////////////////////////
#include "MinCOM/Concurrency/Core/CoreMutex.h"
#include "MinCOM/Concurrency/Core/CoreCounter.h"

// Smart pointers (based on Loki library)
//////////////////////////////////////////////////////////////////////////
#include "MinCOM/Pointers/DualRefCounter.h"
#include "MinCOM/Pointers/Strong.h"
#include "MinCOM/Pointers/Weak.h"
#include "MinCOM/Pointers/BinaryOperators.h"
#include "MinCOM/Pointers/StdExtensions.h"

// Core object model support
//////////////////////////////////////////////////////////////////////////
#include "MinCOM/Common/CallData.h"
#include "MinCOM/Common/ICommon.h"
// #include "MinCOM/Model/ToolsContainer.h"
#include "MinCOM/Common/CommonImpl.h"
#include "MinCOM/Common/Class.h"
#include "MinCOM/Common/Object.h"

// Factory support
//////////////////////////////////////////////////////////////////////////
#include "MinCOM/Factory/IFactory.h"
#include "MinCOM/Factory/FactoryImpl.h"
#include "MinCOM/Factory/CommonHolder.h"
#include "MinCOM/Factory/FactoryHolder.h"

// Variant support for dispatching
//////////////////////////////////////////////////////////////////////////
#include "MinCOM/Variant/CommonVariant.h"
#include "MinCOM/Variant/WrapperT.h"

// Events dispatching, marshaling 
//////////////////////////////////////////////////////////////////////////
#include "MinCOM/Events/Interfaces/IAccessPoint.h"
#include "MinCOM/Events/Interfaces/IAccessProvider.h"
#include "MinCOM/Events/Impl/AccessPointImpl.h"
#include "MinCOM/Events/Impl/AccessProviderImpl.h"

// Commands engine
//////////////////////////////////////////////////////////////////////////
#include "MinCOM/Commands/ICommand.h"
#include "MinCOM/Commands/ICommands.h"
#include "MinCOM/Commands/ICommandEvents.h"
// #include "MinCOM/Model/CommandImpl.h"

// Basic support for concurrency
//////////////////////////////////////////////////////////////////////////
#include "MinCOM/Concurrency/Interfaces/ISynchro.h"
#include "MinCOM/Concurrency/Interfaces/IEvent.h"
#include "MinCOM/Concurrency/Interfaces/IMutex.h"
// #include "MinCOM/Interfaces/ISemaphore.h"
// #include "MinCOM/Interfaces/IThread.h"
// #include "MinCOM/Helpers/Threading.h"

// Logging support
//////////////////////////////////////////////////////////////////////////
// #define INTRENAL_LOG
// #include "MinCOM/Interfaces/ILog.h"




#endif // !MINCOM_H__MINCOM__COMMONKIT__INCLUDED_
