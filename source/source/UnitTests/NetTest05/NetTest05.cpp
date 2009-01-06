#include "Common.h"

#include "../NetTest02/Targets.h"

class Target3
	: public mc::AgentImpl
{
public:

	// IAgent section
	virtual mc::result Invoke(mc::DispId idMember, mc::DispParamsRef dispParams, mc::IVariantWrapperRef result, mc::RefIid /* iid */)
	{

		if ( T3_METHOD_1 == idMember )
		{
			std::cout << "[Target3::T3_METHOD_1] Invoked." << std::endl;
		}

		return mc::_S_OK;
	}

};

int _tmain(int /* argc */, _TCHAR* /* argv[] */)
{

	try
	{

		std::cout << "[main] Attempting to perform any test." << std::endl;

		mc::ICommonPtr remoteTarget1Common = Remoting::Instantiate(CLSID_Target1, Network::InstantiateLocalhost());
		if ( !remoteTarget1Common )
			throw std::exception("[main] Error creating CLSID_Target1.");
		
		std::cout << "[main] Remote Target1 instantiated successfully." << std::endl;

		Remoting::ResponsePtr responseT1M2 = Remoting::CallSync(remoteTarget1Common, T1_METHOD_2, mc::ObjectCreator< Target3 >());
		if ( mc::IsFailed(responseT1M2) )
			throw std::exception("[main] Failed to invoke remote Target1::T2_METHOD_2.");

		std::cout << "[main] Remote Target1::T2_METHOD_2 invoked successfully." << std::endl;

		Remoting::ResponsePtr responseT1M3 = Remoting::CallSync(remoteTarget1Common, T1_METHOD_3);
		if ( mc::IsFailed(responseT1M3) )
			throw std::exception("[main] Failed to invoke remote Target1::T2_METHOD_3.");

		std::cout << "[main] Remote Target1::T2_METHOD_3 invoked successfully." << std::endl;

	}
	catch ( std::exception& e )
	{
		std::cout << "Exception: " << e.what() << "\n";
	}

	return 0;
}