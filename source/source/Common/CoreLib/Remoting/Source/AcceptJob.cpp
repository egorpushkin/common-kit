#include "Common/Common.h"

#include "CommonKit/Project.h"

#include "Remoting/Interfaces/Common.h"

#include "Remoting/Interfaces/IStub.h"

#include "Remoting/Interfaces/IServerInternal.h"

#include "AcceptJob.h"

#include "Remoting/Interfaces/ITransmitter.h"

#include "Stub.h"

#include "Remoting/Tools/Factory.h"

// Messages
#include "Remoting/Messages/Codes.h"
#include "Remoting/Messages/MessagesMap.h"
#include "Remoting/Messages/InstRespMsg.h"

namespace Remoting
{

	AcceptJob::AcceptJob()
		: mc::AgentImpl()
	{
	}

	// IAgent section
	mc::result AcceptJob::Invoke(mc::DispId idMember, mc::DispParamsRef dispParams, mc::IVariantWrapperRef /* result */, mc::RefIid /* iid */)
	{		

		if ( idMember == Components::AGENTID_MAINJOBCALL )
		{
			// Accept params
			if ( dispParams->GetCount() < 2 )
				return mc::_E_FAIL;

			Remoting::IServerInternalPtr serverInternal(dispParams->Get(1)->toCommon(), IID_IServerInternal);
			Network::IClientPtr client(dispParams->Get(0)->toCommon(), Network::IID_IClient);

			return HandleAccept(serverInternal, client);
		}

		return mc::_S_OK;
	}

	mc::result AcceptJob::HandleAccept(Remoting::IServerInternalRef serverInternal, Network::IClientRef client)
	{
		if ( !serverInternal || !client )
			return mc::_E_FAIL;

		Network::IProtocolPtr protocol = MessagesMap::InstantiateProtocol();
		if ( !protocol )
			return mc::_E_FAIL;

		if ( mc::IsFailed(protocol->AttachGateway(client)) )
			return mc::_E_FAIL;

		Network::IMessagePtr msg = protocol->Receive();
		if ( !msg )
			return mc::_E_FAIL;

		const Network::IMessage::Code_ code = msg->GetCode();
		if ( code == MSGCODE_INST )
		{
			// Instantiate new server-side object
			//////////////////////////////////////////////////////////////////////////
			
			// Create stub to handle new connection
			IStubPtr stub = IStubPtr(mc::ObjectCreator< Stub >(), IID_IStub);
			if ( !stub )
				return mc::_E_FAIL;

			// Register server as parent for newly created object
			mc::IItemPtr stubItem(stub, mc::IID_IItem);
			if ( stubItem )
				stubItem->SetParent(mc::ICommonPtr(serverInternal, mc::IID_ICommon));

			// Generate unique client id
			Network::IClient::Id_ clientId = serverInternal->GenerateUniqueClientId();
			mc::Clsid objId = msg->GetProperty(MSGPROP_OBJCLSID).toGuid();

			// Configure proxy
			mc::result response = stub->Initialize(protocol, clientId, objId);

			if ( mc::IsSucceeded(response) )
			{
				serverInternal->RegisterStub(stub);	
			}

			Network::IMessagePtr instRespMsg(
				mc::ObjectCreator< InstRespMsg >(clientId, response), Network::IID_IMessage);
			if ( mc::IsFailed(protocol->Send(instRespMsg)) )
				return mc::_E_FAIL;
		}
		else if ( code == MSGCODE_INSTCHILD_PROX )
		{
			// Create server-side proxy for transmitted client-side object
			//////////////////////////////////////////////////////////////////////////
			
			void* ptr = msg->GetProperty(MSGPROP_OBJPTRID).toPVoid();
			Network::IClient::Id_ clientId = msg->GetProperty(MSGPROP_CLIENTID).toULong();

			// Construct and configure dispatcher
			mc::ICommonPtr proxyCommon = InstantiateProxy(
				protocol, 
				clientId,
				IServerPtr(serverInternal, IID_IServer),
				SERVER_SIDE,
				NULL);
			if ( !proxyCommon )
				return mc::_S_OK;

			serverInternal->AttachObject(ptr, clientId, proxyCommon);

			Network::IMessagePtr instRespMsg(
				mc::ObjectCreator< InstRespMsg >(clientId, mc::_S_OK), Network::IID_IMessage);
			if ( mc::IsFailed(protocol->Send(instRespMsg)) )
				return NULL;
		}
		else if ( code == MSGCODE_INSTCHILD_DISP )
		{
			// Create server-side stub for transmitted server-side object
			//////////////////////////////////////////////////////////////////////////

			void* ptr = msg->GetProperty(MSGPROP_OBJPTRID).toPVoid();
			Network::IClient::Id_ clientId = msg->GetProperty(MSGPROP_CLIENTID).toULong();

			// Find transmitted object
			mc::ICommonPtr localTarget = serverInternal->RemitProxy(ptr, 0);
			if ( !localTarget )
				return mc::_S_OK;

			// Create stub to handle new connection
			IStubPtr stub = IStubPtr(mc::ObjectCreator< Stub >(), IID_IStub);
			if ( !stub )
				return mc::_S_OK;

			// Register server as parent for newly created object
			mc::IItemPtr stubItem(stub, mc::IID_IItem);
			if ( stubItem )
				stubItem->SetParent(mc::ICommonPtr(serverInternal, mc::IID_ICommon));

			// Configure proxy
			mc::result response = stub->Initialize(
				protocol, 
				clientId, 
				localTarget, 
				SERVER_SIDE, 
				NULL);

			if ( mc::IsSucceeded(response) )
			{
				serverInternal->RegisterStub(stub);	
			}

			Network::IMessagePtr instRespMsg(
				mc::ObjectCreator< InstRespMsg >(clientId, response), Network::IID_IMessage);
			if ( mc::IsFailed(protocol->Send(instRespMsg)) )
				return mc::_E_FAIL;
		} 

		return mc::_S_OK;
	}

}
