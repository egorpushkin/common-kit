#include "Common.h"

#include "../NetTest02/Targets.h"

int _tmain(int /* argc */, _TCHAR* /* argv[] */)
{

	try
	{

		std::cout << "[main] Attempting to perform any test." << std::endl;

		mc::ICommonPtr remoteTarget1Common = Remoting::Instantiate(CLSID_Target1, Network::InstantiateLocalhost());
		if ( !remoteTarget1Common )
			throw std::exception("[main] Error creating CLSID_Target1.");
		
		std::cout << "[main] Remote Target1 instantiated successfully." << std::endl;

		Remoting::ResponsePtr responseT1M1 = Remoting::CallSync(remoteTarget1Common, T1_METHOD_1);
		if ( mc::IsFailed(responseT1M1) )
			throw std::exception("[main] Failed to invoke remote Target1::T2_METHOD_1.");

		std::cout << "[main] Remote Target1::T2_METHOD_1 invoked successfully." << std::endl;

		if ( mc::Variant::CE_COMMON != responseT1M1->GetRetVal().type() )
			throw std::exception("[main] Target1::T2_METHOD_1 returned wrong result.");

		mc::ICommonPtr remoteTarget2Common = responseT1M1->GetRetVal().toCommon();
		if ( !remoteTarget2Common )
			throw std::exception("[main] Wrong remote Target2 acquired.");

		// Demo must continue correct execution even if the first transmitted object
		//  would be destroyed.
		// remoteTarget1Common = NULL;
 
		Remoting::ResponsePtr responseT2M1 = Remoting::CallSync(remoteTarget2Common, T2_METHOD_1);
		if ( mc::IsFailed(responseT2M1) )
			throw std::exception("[main] Failed to invoke remote Target2::T2_METHOD_1.");

		std::cout << "[main] Remote Target2::T2_METHOD_1 invoked successfully." << std::endl;

		Remoting::ResponsePtr responseT2M2 = Remoting::CallSync(remoteTarget2Common, T2_METHOD_2);
		if ( mc::IsFailed(responseT2M2) )
			throw std::exception("[main] Failed to invoke remote Target2::T2_METHOD_2.");

		std::cout << "[main] Remote Target2::T2_METHOD_2 returned: " << responseT2M2->GetRetVal().toFloat() << std::endl;

		// Remote interaction with external object (towards server)
		//////////////////////////////////////////////////////////////////////////
		mc::ICommonPtr remotePoint = Remoting::Instantiate(CLSID_CustomPoint, Network::InstantiateLocalhost());
		if ( !remotePoint )
			throw std::exception("[main] Error creating CLSID_CustomPoint.");

		std::cout << "[main] Remote CLSID_CustomPoint instantiated successfully." << std::endl;


	
	}
	catch ( std::exception& e )
	{
		std::cout << "Exception: " << e.what() << "\n";
	}

	return 0;
}
