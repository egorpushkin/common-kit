#include "Common/Common.h"

#include "Remoting/Interfaces/Common.h"

#include "Remoting/Interfaces/ITransmitter.h"

#include "Remoting/Messages/MessagesMap.h"

#include "Remoting/Messages/Codes.h"

#include "Transmitter.h"

#include "Remoting/Interfaces/IStub.h"

#include "Remoting/Interfaces/IServerInternal.h"

#include "Remoting/Messages/MessagesMap.h"

#include "Remoting/Messages/InstChildMsg.h"

#include "Remoting/Messages/InstChildProxMsg.h"

#include "Remoting/Messages/InstChildDispMsg.h"

#include "Remoting/Messages/Codes.h"

#include "Remoting/Source/Stub.h"

#include "Remoting/Tools/Factory.h"

namespace Remoting
{

	Transmitter::Transmitter()
		: mc::CommonImpl< ITransmitter >()
	{
	}

	// ICommon section
	BEGIN_INTERFACE_MAP(Transmitter)
		COMMON(ITransmitter)
		INTERFACE(ITransmitter)
	END_INTERFACE_MAP()		

	// ITransmitter section
	mc::result Transmitter::Transmit(
		Behaviour mode, 
		mc::ICommonRef object,
		Network::IClient::Id_ clientId,						
		IServerRef server,
		Network::IHostRef host)
	{
		if ( !object )
			return mc::_S_FALSE;

		if ( !server )
			return mc::_E_FAIL;

		IServerInternalPtr serverInternal(server, IID_IServerInternal);
		if ( !serverInternal )
			return mc::_E_FAIL;

		if ( CLIENT_SIDE == mode )
		{
			// Initiate connection and configure session
			Network::IProtocolPtr connectionHolder;
			if ( mc::IsFailed(ConnectToServer< InstChildProxMsg >(
				host,
				object.GetPointer(),
				clientId,
				connectionHolder)) || !connectionHolder )
				return mc::_E_FAIL;

			// Create stub to handle new connection
			IStubPtr stub = IStubPtr(mc::ObjectCreator< Stub >(), IID_IStub);
			if ( !stub )
				return mc::_E_FAIL;

			// Register server as parent for newly created object
			mc::IItemPtr stubItem(stub, mc::IID_IItem);
			if ( stubItem )
				stubItem->SetParent(mc::ICommonPtr(server, mc::IID_ICommon));

			// Configure stub
			if ( mc::IsFailed(stub->Initialize(connectionHolder, clientId, object, mode, host)) )
				return mc::_E_FAIL;

			// Register stub
			return serverInternal->RegisterStub(stub);
		}
		else if ( SERVER_SIDE == mode )
		{
			// Register object which must be requested by client in specific way
			return serverInternal->AttachObject(object.GetPointer(), 0, object);
		}
		else
			return mc::_E_FAIL;
	}

	mc::ICommonPtr Transmitter::Obtain(
		Behaviour mode, 
		void* ptr,
		Network::IClient::Id_ clientId,						
		IServerRef server,
		Network::IHostRef host)
	{
		if ( !ptr )
			return NULL;

		if ( !server )
			return NULL;

		if ( CLIENT_SIDE == mode )
		{
			// Initiate connection and configure session
			Network::IProtocolPtr connectionHolder;
			if ( mc::IsFailed(ConnectToServer< InstChildDispMsg >(
				host,
				ptr,
				clientId,
				connectionHolder)) || !connectionHolder )
				return NULL;

			// Construct stub
			return InstantiateProxy(connectionHolder, clientId, server, mode, host);
		}
		else if ( SERVER_SIDE == mode )
		{
			IServerInternalPtr serverInternal(server, IID_IServerInternal);
			if ( !serverInternal )
				return NULL;

			return serverInternal->RemitProxy(ptr, clientId);	
		}
		else
			return NULL;
	}

}
