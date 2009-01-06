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

template < class T >
std::string ToString(T value)
{
	std::stringstream stream;
	stream << value;
	std::string retVal;
	stream >> retVal;
	return retVal;
}

mc::ICommonPtr Retransmit(mc::ICommonPtr remoteTarget, mc::ICommonRef object, bool history, unsigned int level)
{
	// Retransmit object
	Remoting::ResponsePtr remoteResponse = Remoting::CallSync(remoteTarget, T1_METHOD_4, object, T3_METHOD_1, history);
	if ( mc::IsFailed(remoteResponse) )
	{
		std::string msg = 
			std::string("[ReTransmit] Failed to invoke remote Target1::T2_METHOD_4 (Level ") + 
			ToString(level) + 
			std::string(").");
		throw std::exception(msg.c_str());
	}

	std::cout 
		<< "[ReTransmit] Remote Target1::T2_METHOD_4 (Level " 
		<< level 
		<< ") invoked successfully."
		<< std::endl;

	mc::ICommonPtr transmittedObject = remoteResponse->GetRetVal().toCommon();
	if ( !transmittedObject )
	{
		std::string msg = 
			std::string("[ReTransmit] Wrong object returned by Target1::T2_METHOD_4 (Level ") + 
			ToString(level) + 
			std::string(").");
		throw std::exception(msg.c_str());
	}

	// Test transmitted object
	Remoting::ResponsePtr localResponse = Remoting::CallSync(transmittedObject, T3_METHOD_1);
	if ( mc::IsFailed(localResponse) )
	{
		std::string msg = 
			std::string("[ReTransmit] Failed to invoke Transmitted Target3::T2_METHOD_1 (Level ") + 
			ToString(level) + 
			std::string(").");
		throw std::exception(msg.c_str());
	}

	std::cout 
		<< "[main] Transmitted Target3::T2_METHOD_1 (Level "
		<< level 
		<< ") invoked successfully." 
		<< std::endl;

	return transmittedObject;	
}

const bool maintainHistory = true;

int _tmain(int /* argc */, _TCHAR* /* argv[] */)
{

	try
	{

		std::cout << "[main] Attempting to perform any test." << std::endl;

		mc::ICommonPtr remoteTarget1Common = Remoting::Instantiate(CLSID_Target1, Network::InstantiateLocalhost());
		if ( !remoteTarget1Common )
			throw std::exception("[main] Error creating CLSID_Target1.");
		
		std::cout << "[main] Remote Target1 instantiated successfully." << std::endl;

		// Initial transmission
		mc::ICommonPtr transmittedLevel1 = Retransmit(
			remoteTarget1Common,
			mc::ObjectCreator< Target3 >(),
			maintainHistory,
			1);

		Objects transmissionHistory;
		
		if ( maintainHistory )
			transmissionHistory.push(transmittedLevel1);

		mc::ICommonPtr transmittedLevelN = transmittedLevel1;
		
		for ( unsigned int i = 0 ; i < 9 ; ++i )
		{
			transmittedLevelN = Retransmit(
				remoteTarget1Common,
				transmittedLevelN,
				maintainHistory,
				i + 2);

			if ( maintainHistory )
				transmissionHistory.push(transmittedLevelN);
		}

	}
	catch ( std::exception& e )
	{
		std::cout << "Exception: " << e.what() << "\n";
	}

	return 0;
}