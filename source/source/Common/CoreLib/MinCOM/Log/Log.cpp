#include "Common/Common.h"

#include "Log.h"

#include <iostream>

namespace MinCOM
{

	Log::Log()
		: CommonImpl< ILog >()
	{
	}

	Log::~Log()
	{
	}

	// ICommon section
	BEGIN_INTERFACE_MAP(Log)
		COMMON(ILog)
		INTERFACE_(ILog, IID_ILog)
	END_INTERFACE_MAP()	

	// ILog section
	result Log::Notify(const String& message)
	{

#ifdef _UNICODE
		std::wcout << message << std::endl;		
#else // _UNICODE
		std::cout << message << std::endl;		
#endif // _UNICODE

		return _S_OK;
	}

	// Holder
	typedef Loki::SingletonHolder
	<
		mc::CommonHolder< Log >,
		Loki::CreateUsingNew,
		Loki::PhoenixSingleton
	> 
	LogHolder;	

	// External tools
	ILogPtr InstantiateLog()
	{
		return ILogPtr(LogHolder::Instance().GetInstance(), IID_ILog);
	}

}
