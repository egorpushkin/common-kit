#include "Common.h"

#include "../NetTest02/Targets.h"

int _tmain(int /* argc */, _TCHAR* /* argv[] */)
{

	try
	{

		mc::ICommonPtr remoteTarget2Common = Remoting::Instantiate(CLSID_Target2, Network::InstantiateLocalhost());
		if ( !remoteTarget2Common )
			throw std::exception("[main] Error creating CLSID_Target2.");
		
		std::cout << "[main] Remote Target2 instantiated successfully." << std::endl;

		Remoting::ResponsePtr response = Remoting::CallSync(remoteTarget2Common, T2_METHOD_1);
		if ( mc::IsFailed(response) )
			throw std::exception("[main] Failed to invoke remote Target2 T2_METHOD_1.");
 
		std::cout << "[main] Remote Target2 T2_METHOD_1 invoked successfully." << std::endl;
	
	}
	catch ( std::exception& e )
	{
		std::cout << "Exception: " << e.what() << "\n";
	}

	return 0;
}
