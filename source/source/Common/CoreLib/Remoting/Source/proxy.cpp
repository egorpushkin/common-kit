#include "Common/Common.h"

#include "Remoting/Interfaces/Common.h"

#include "Remoting/Interfaces/IStub.h"

#include "Remoting/Interfaces/ITransmitter.h"

#include "Remoting/Interfaces/IProxy.h"

#include "Proxy.h"

#include "Remoting/Tools/Factory.h"

#include "Remoting/Interfaces/IServerInternal.h"

#include "Server.h"

#include "Remoting/Messages/MessagesMap.h"

#include "Remoting/Messages/Codes.h"

#include "Transmitter.h"

// Messages
#include "Remoting/Messages/Codes.h"
#include "Remoting/Messages/MessagesMap.h"
#include "Remoting/Messages/InstMsg.h"
#include "Remoting/Messages/InstRespMsg.h"
#include "Remoting/Interfaces/IInvokeMsg.h"
#include "Remoting/Messages/InvokeMsg.h"
#include "Remoting/Messages/InvokeRespMsg.h"

namespace Remoting
{

	Proxy::Proxy()
		: mc::CommonImpl< IProxy >()
		, mc::AgentImpl()
		, lock_(mc::InstantiateMutex())
		, mode_(UNDEFINED)
		, transmitter_(mc::ObjectCreator< Transmitter >(), IID_ITransmitter)
		, protocol_()
		, host_()
		, server_()
		, clientId_(0)
	{
	}

	// ICommon section
	BEGIN_INTERFACE_MAP(Proxy)
		COMMON(IProxy)
		INTERFACE(IProxy)
		IMPL(mc::AgentImpl)
		IMPL(mc::ItemImpl)
	END_INTERFACE_MAP()	

	// IProxy section
	mc::result Proxy::Instantiate(mc::RefClsid clsid, Network::IHostRef host)
	{
		mc::MutexLock lock(lock_);

		if ( protocol_ || !host )
			return mc::_E_FAIL;

		// Initiate connection and configure session
		Network::IClientPtr route = Network::InstantiateClient();
		if ( !route )
			return mc::_E_FAIL;

		if ( mc::IsFailed(route->Connect(host)) )
			return mc::_E_FAIL;

		protocol_ = MessagesMap::InstantiateProtocol();
		if ( !protocol_ )
			return mc::_E_FAIL;

		if ( mc::IsFailed(protocol_->AttachGateway(route)) )
			return mc::_E_FAIL;

		// Start server to handle async notifications
		server_ = GetGlobalServer();
		if ( !server_ )
			return mc::_E_FAIL;

		IServerInternalPtr serverInternal(server_, IID_IServerInternal);
		if ( !serverInternal )
			return NULL;
		
		serverInternal->RunPassive();

		Network::IMessagePtr instMsg(mc::ObjectCreator< InstMsg >(clsid), Network::IID_IMessage);
		if ( !instMsg )
			return mc::_E_FAIL;

		if ( mc::IsFailed(protocol_->Send(instMsg)) )
			return mc::_E_FAIL;

		Network::IMessagePtr instRespMsg = protocol_->Receive();
		if ( !instRespMsg || MSGCODE_INST_RESP != instRespMsg->GetCode() )
			return mc::_E_FAIL;
		
		clientId_ = instRespMsg->GetProperty(MSGPROP_CLIENTID).toULong();
		mc::result response = instRespMsg->GetProperty(MSGPROP_RESPONSE).toLong();

		if ( mc::IsFailed(response) )
			return mc::_E_FAIL;

		// Remember machine for further active interaction with server
		host_ = host;

		mode_ = CLIENT_SIDE;

		return mc::_S_OK;
	}

	mc::result Proxy::Instantiate(Network::IProtocolRef protocol, Network::IClient::Id_ clientId, IServerRef server, Behaviour mode, Network::IHostRef host)
	{
		mc::MutexLock lock(lock_);

		if ( protocol_ || !protocol || !server )
			return NULL;

		protocol_ = protocol;	

		clientId_ = clientId;

		server_ = server;

		mode_ = mode;

		host_ = host;

		return mc::_S_OK;
	}

	// IAgent section
	mc::result Proxy::Invoke(mc::DispId idMember, mc::DispParamsRef dispParams, mc::IVariantWrapperRef result, mc::RefIid iid)
	{				
		mc::MutexLock lock(lock_);

		if ( !protocol_ )
			return mc::_E_FAIL;

		// 1. Check for objects among arguments and transmit if required
		unsigned int paramsCount = 0;
		if ( dispParams )
			paramsCount = dispParams->GetCount();
		for ( unsigned int i = 0 ; i < paramsCount ; ++i )
		{
			if ( mc::Variant::CE_COMMON == dispParams->GetRef(i).type() )
			{
				// Object found. It must be transmitted to server. Transmitter is responsible for this operation.
				if ( mc::IsFailed(transmitter_->Transmit(
					mode_,
					dispParams->GetRef(i).toCommon(),
					clientId_,
					server_,
					host_)) )
					return mc::_E_FAIL;
			}
		}

		// 2. Send request
		Network::IMessagePtr invokeMsg(mc::ObjectCreator< InvokeMsg >(idMember, dispParams, iid), Network::IID_IMessage);
		if ( !invokeMsg )
			return mc::_E_FAIL;

		if ( mc::IsFailed(protocol_->Send(invokeMsg)) )
			return mc::_E_FAIL;

		// 3. Read response
		Network::IMessagePtr invokeRespMsg = protocol_->Receive();
		if ( !invokeRespMsg || MSGCODE_INVOKE_RESP != invokeRespMsg->GetCode() )
			return mc::_E_FAIL;

		mc::result response = invokeRespMsg->GetProperty(MSGPROP_RESPONSE).toLong();
		mc::Variant& retVal = invokeRespMsg->GetProperty(MSGPROP_RETVAL);

		if ( ( mc::Variant::CE_BYPTR | mc::Variant::CE_COMMON ) == retVal.type() )
		{
			// Establish one more connection to server
			retVal = mc::Variant(
				transmitter_->Obtain(
					mode_, 
					retVal.toPCommon(),
					clientId_,
					server_,
					host_));	
		}
		
		if ( result )
			result->SetData(retVal);
		
		return response;
	}

}
