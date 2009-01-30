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

// Core interfaces
//////////////////////////////////////////////////////////////////////////
#include "MinCOM/Common/ICommon.h"
// #include "MinCOM/Model/ToolsContainer.h"
#include "MinCOM/Common/CommonImpl.h"
#include "MinCOM/Common/Object.h"

// Factory support
//////////////////////////////////////////////////////////////////////////
// #include "MinCOM/Factory/Factory.h"
// #include "MinCOM/Factory/Holder.h"
// #include "MinCOM/Factory/Tools.h"

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

// Simple factory 
//////////////////////////////////////////////////////////////////////////
// #include "MinCOM/Interfaces/IFactory.h"
// #include "MinCOM/Model/FactoryImpl.h"


// Commands engine
//////////////////////////////////////////////////////////////////////////
// #include "MinCOM/Interfaces/ICommand.h"
// #include "MinCOM/Interfaces/ICommands.h"
// #include "MinCOM/Model/CommandImpl.h"


// Threading support
//////////////////////////////////////////////////////////////////////////
// #include "MinCOM/Interfaces/ISynchro.h"
// #include "MinCOM/Interfaces/IMultiSynchro.h"
// #include "MinCOM/Interfaces/ISynchroHandle.h"
// #include "MinCOM/Interfaces/IEvent.h"
// #include "MinCOM/Interfaces/IMutex.h"
// #include "MinCOM/Interfaces/ISemaphore.h"
// #include "MinCOM/Interfaces/IThread.h"
// #include "MinCOM/Helpers/Threading.h"

// Logging support
//////////////////////////////////////////////////////////////////////////
// #define INTRENAL_LOG
// #include "MinCOM/Interfaces/ILog.h"




#endif // !MINCOM_H__MINCOM__COMMONKIT__INCLUDED_
