// CoreTest03.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#ifdef _MSC_VER 
#include <crtdbg.h>
#endif // _MSC_VER

#include <iostream>

#include "CommonKit/MinCOM.h"

#include <boost/tr1/memory.hpp>
#include <boost/tr1/functional.hpp>

namespace std
{
	namespace tr1
	{
		using namespace boost;
	}
}

/*
std::tr1::shared_ptr< mc::IAgent > make_shared_from_COM(mc::IAgent* p)
{
	p->AddRef();
	std::tr1::shared_ptr< mc::IAgent > pw(p, std::tr1::mem_fn(&mc::IAgent::Release));
	return pw;
}
*/

template
<
	class T
>
std::tr1::shared_ptr< T > ConstructPointer(T* p)
{
	p->AddRef();
	std::tr1::shared_ptr< T > pw(p, std::tr1::mem_fn(&T::Release));
	return pw;
}

typedef std::tr1::shared_ptr< mc::IAgent > IAgentBoostPtr;

typedef std::tr1::weak_ptr< mc::IAgent > IAgentBoostWeak;

int _tmain(int argc, _TCHAR* argv[])
{

	{

		mc::IAgentPtr agent(mc::ObjectCreator< mc::AgentImpl >(), mc::IID_IAgent);

		IAgentBoostPtr boostAgent(ConstructPointer(GetImpl(agent)));

		IAgentBoostWeak boostAgentWeak(boostAgent);

		// boostAgent.reset();

		if ( IAgentBoostPtr boostAgent2 = boostAgentWeak.lock() )
		{

			std::cout << "Nice";

		}
		else
		{

			std::cout << "Fuck";

		}
		
	}

#ifdef _MSC_VER 
	_CrtDumpMemoryLeaks(); 
#endif // _MSC_VER

	return 0;
}

