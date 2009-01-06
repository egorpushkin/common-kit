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
		else if ( T3_METHOD_2 == idMember )
		{
			std::cout << "[Target3::T3_METHOD_2] Invoked." << std::endl;

			// Accept remote target2
			if ( dispParams->GetCount() != 1 )
			{
				std::cout << "[Target3::T1_METHOD_2] Wrong parameters were passed." << std::endl;
				return mc::_E_FAIL;
			}

			remoteTarget2_ = dispParams->Get(0)->toCommon();
			if ( !remoteTarget2_ )
			{
				std::cout << "[Target3::T1_METHOD_2] Wrong remote target object passed." << std::endl;
				return mc::_E_FAIL;
			}

			std::cout << "[Target3::T1_METHOD_2] Remote Target2 transmitted successfully." << std::endl;

			// Invoke remote Target2::T2_METHOD_1
			Remoting::ResponsePtr responseT2M1 = Remoting::CallSync(remoteTarget2_, T2_METHOD_1);
			if ( mc::IsFailed(responseT2M1) )
			{
				std::cout << "[Target3::T1_METHOD_2] Failed to invoke remote Target2::T2_METHOD_1." << std::endl;
				return mc::_E_FAIL;
			}

			std::cout << "[Target3::T1_METHOD_2] Remote Target2::T2_METHOD_1 invoked successfully." << std::endl;

			// Return remote target2 back
			if ( !result )
			{
				std::cout << "[Target3::T1_METHOD_2] Wrong result wrapper prepared for the call." << std::endl;
				return mc::_E_FAIL;
			}

			result->SetData(remoteTarget2_);

			std::cout << "[Target3::T3_METHOD_2] Completed." << std::endl;
		}

		return mc::_S_OK;
	}

private:

	mc::ICommonPtr remoteTarget2_;

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

		// Transmit Traget3 to server
		Remoting::ResponsePtr responseT1M3 = Remoting::CallSync(remoteTarget1Common, T1_METHOD_2, mc::ObjectCreator< Target3 >());
		if ( mc::IsFailed(responseT1M3) )
			throw std::exception("[main] Failed to invoke remote Target1::T2_METHOD_2.");

		// Initiate remote invocation of Target3::T3_METHOD_2
		Remoting::ResponsePtr responseT1M5 = Remoting::CallSync(remoteTarget1Common, T1_METHOD_5);
		if ( mc::IsFailed(responseT1M5) )
			throw std::exception("[main] Failed to invoke remote Target1::T2_METHOD_5.");

		std::cout << "[main] Remote Target1::T2_METHOD_5 invoked successfully." << std::endl;

	}
	catch ( std::exception& e )
	{
		std::cout << "Exception: " << e.what() << "\n";
	}

	return 0;
}