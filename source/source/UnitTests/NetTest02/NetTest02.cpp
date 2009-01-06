#include "Common.h"

#include "Targets.h"

// Areas
//////////////////////////////////////////////////////////////////////////
#include "AreasKit/AreasKit.h"

// Targets' implementation
//////////////////////////////////////////////////////////////////////////

class Target2
	: public mc::AgentImpl
{
public:

	// IAgent section
	virtual mc::result Invoke(mc::DispId idMember, mc::DispParamsRef dispParams, mc::IVariantWrapperRef result, mc::RefIid /* iid */)
	{

		if ( T2_METHOD_1 == idMember )
		{
			std::cout << "[Target2::T2_METHOD_1] invoked." << std::endl;
		}
		else if ( T2_METHOD_2 == idMember )
		{
			std::cout << "[Target2::T2_METHOD_2] invoked." << std::endl;

			if ( result )
			{
				result->SetData(10.5f);

				std::cout << "[Target2::T1_METHOD_2] 10.5f returned to client." << std::endl;
			}
		}

		return mc::_S_OK;
	}

};

class Target1
	: public mc::AgentImpl
{
public:

	Target1()
		: target2_(mc::ObjectCreator< Target2 >())
		, remoteTarget3_()
		, remoteObjects_()
	{
	}

	// IAgent section
	virtual mc::result Invoke(mc::DispId idMember, mc::DispParamsRef dispParams, mc::IVariantWrapperRef result, mc::RefIid /* iid */)
	{

		if ( T1_METHOD_1 == idMember )
		{
			std::cout << "[Target1::T1_METHOD_1] Invoked." << std::endl;

			// Give back object (target2_) as return value
			if ( result )
			{
				result->SetData(target2_);

				std::cout << "[Target1::T1_METHOD_1] Target2 returned to client." << std::endl;
			}
			else
			{
				std::cout << "[Target1::T1_METHOD_1] Result wrapper is missing." << std::endl;
				return mc::_E_FAIL;
			}
		}
		else if ( T1_METHOD_2 == idMember )
		{
			std::cout << "[Target1::T1_METHOD_2] Invoked." << std::endl;

			// Accept remote object from client
			if ( dispParams->GetCount() > 0 )
			{
				remoteTarget3_ = dispParams->Get(0)->toCommon();
				if ( remoteTarget3_ )
				{
					std::cout << "[Target1::T1_METHOD_2] RemoteTarget3 transmitted successfully." << std::endl;
				}
				else
				{
					std::cout << "[Target1::T1_METHOD_2] Wrong remote target parameter." << std::endl;
					return mc::_E_FAIL;
				}
			}
			else
			{
				std::cout << "[Target1::T1_METHOD_2] Wrong parameters were passed." << std::endl;
				return mc::_E_FAIL;
			}
		}
		else if ( T1_METHOD_3 == idMember )
		{
			std::cout << "[Target1::T1_METHOD_3] Invoked." << std::endl;

			mc::IAgentPtr remoteTarget3Agent_(remoteTarget3_, mc::IID_IAgent);
			if ( remoteTarget3Agent_ )
			{
				remoteTarget3Agent_->Invoke(T3_METHOD_1);

				std::cout << "[Target1::T1_METHOD_3] T3_METHOD_1 invoked." << std::endl;
			}
			else
			{
				std::cout << "[Target1::T1_METHOD_3] Remote target does not support IAgent." << std::endl;
				return mc::_E_FAIL;
			}
		}
		else if ( T1_METHOD_4 == idMember )
		{
			std::cout << "[Target1::T1_METHOD_4] Invoked." << std::endl;

			// Accept remote object from client
			if ( dispParams->GetCount() != 3 )
			{
				std::cout << "[Target1::T1_METHOD_4] Wrong input arguments." << std::endl;
				return mc::_E_FAIL;
			}

			bool storeHistory = dispParams->Get(0)->toBool();
			mc::DispId methodId = dispParams->Get(1)->toLong();
			
			// Acquire transmitted object from arguments
			mc::ICommonPtr remoteObject = dispParams->Get(2)->toCommon();
			if ( !remoteObject )
			{
				std::cout << "[Target1::T1_METHOD_4] Wrong object accepted." << std::endl;
				return mc::_E_FAIL;
			}

			// Perform test call to object
			Remoting::ResponsePtr remoteResponse = Remoting::CallSync(remoteObject, methodId);
			if ( mc::IsFailed(remoteResponse) )
			{
				std::cout << "[Target1::T1_METHOD_4] Failed to invoke method of transmitted object." << std::endl;
				return mc::_E_FAIL;
			}

			std::cout << "[Target1::T1_METHOD_4] Method of transmitted object successfully called." << std::endl;

			// Retransmit object returning it back to caller
			if ( !result )
			{
				std::cout << "[Target1::T1_METHOD_4] Wrong response acceptor constructed and passed." << std::endl;
				return mc::_E_FAIL;
			}

			result->SetData(remoteObject);

			// Maintain history of transmitted objects
			if ( storeHistory )
				remoteObjects_.push(remoteObject);

			std::cout << "[Target1::T1_METHOD_4] Remote object successfully accepted and returned." << std::endl;
		}
		else if ( T1_METHOD_5 == idMember )
		{
			std::cout << "[Target1::T1_METHOD_5] Invoked." << std::endl;

			if ( !remoteTarget3_ )
			{
				std::cout << "[Target1::T1_METHOD_5] Remote target3 was not configured." << std::endl;
				return mc::_E_FAIL;
			}

			// Perform call to remote target3
			Remoting::ResponsePtr responseT3M2 = Remoting::CallSync(remoteTarget3_, T3_METHOD_2, target2_);
			if ( mc::IsFailed(responseT3M2) )
			{
				std::cout << "[Target1::T1_METHOD_5] Failed to invoke remote target3::T3_METHOD_2." << std::endl;
				return mc::_E_FAIL;
			}

			// Acquire returned transmitted target2 object
			mc::ICommonPtr transmittedTarget2 = responseT3M2->GetRetVal().toCommon();
			if ( !transmittedTarget2 )
			{
				std::cout << "[Target1::T1_METHOD_5] Wrong transmitted target2 object returned." << std::endl;
				return mc::_E_FAIL;
			}

			// Perform test call to transmitted target2 object
			Remoting::ResponsePtr responseT3M1 = Remoting::CallSync(transmittedTarget2, T3_METHOD_1);
			if ( mc::IsFailed(responseT3M1) )
			{
				std::cout << "[Target1::T1_METHOD_5] Failed to invoke remote target3::T3_METHOD_1." << std::endl;
				return mc::_E_FAIL;
			}

			std::cout << "[Target1::T1_METHOD_5] Completed." << std::endl;			
		}

		return mc::_S_OK;
	}

private:

	mc::ICommonPtr target2_;

	mc::ICommonPtr remoteTarget3_;

	Objects remoteObjects_;

};

int _tmain(int /* argc */, _TCHAR* /* argv[] */)
{

	try
	{
	
		// Instantiate main remoting service object
		Remoting::IServerPtr server = Remoting::InstantiateServer();
		
		// Attach sample targets
		mc::IItemPtr serverItem(server, mc::IID_IItem);
		if ( serverItem )
		{		
			serverItem->Attach(CLSID_Target1, mc::ObjectCreator< Target1 >());
			serverItem->Attach(CLSID_Target2, mc::ObjectCreator< Target2 >());
			
			serverItem->Attach(CLSID_CustomPoint, Components::InstantiateCommon(Areas::CLSID_Point));			
		}
		
		// Start remoting service
		server->Run(Network::InstantiateLocalhost()); 

	}
	catch ( std::exception& e )
	{
		std::cout << "Exception: " << e.what() << "\n";
	}

	return 0;
}