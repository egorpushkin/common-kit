namespace Remoting
{

	template < class TMessage >
	mc::result Transmitter::ConnectToServer(
		Network::IHostRef host,
		void* ptr,
		Network::IClient::Id_ clientId, 		
		Network::IProtocolPtr& connectionHolder)
	{
		if ( !host )
			return mc::_E_FAIL;

		// Initiate connection and configure session
		Network::IClientPtr connection = Network::InstantiateClient();
		if ( !connection )
			return mc::_E_FAIL;

		if ( mc::IsFailed(connection->Connect(host)) )
			return mc::_E_FAIL;

		connectionHolder = MessagesMap::InstantiateProtocol();
		if ( !connectionHolder || mc::IsFailed(connectionHolder->AttachGateway(connection)) )
			return mc::_E_FAIL;

		// Send connection code, local object id and client id
		Network::IMessagePtr instChildMsg(mc::ObjectCreator< TMessage >(ptr, clientId), Network::IID_IMessage);
		if ( !instChildMsg )
			return mc::_E_FAIL;

		if ( mc::IsFailed(connectionHolder->Send(instChildMsg)) )
			return mc::_E_FAIL;

		// Read response
		Network::IMessagePtr instRespMsg = connectionHolder->Receive();
		if ( !instRespMsg || MSGCODE_INST_RESP != instRespMsg->GetCode() )
			return mc::_E_FAIL;

		mc::result response = instRespMsg->GetProperty(MSGPROP_RESPONSE).toLong();
		if ( mc::IsFailed(response) )
			return mc::_E_FAIL;	

		return mc::_S_OK;
	}

}
