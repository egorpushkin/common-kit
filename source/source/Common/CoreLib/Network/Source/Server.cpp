#include "Common/Common.h"

#include "CommonKit/Network.h"

#include "Session.h"

#include "Server.h"

#include "Client.h"

#include "Service.h"

namespace Network
{

	Server::Server()
		: mc::CommonImpl< IServer >()
		, mc::APImpl()
		, acceptor_()
	{
	}

	// ICommon section
	BEGIN_INTERFACE_MAP(Server)
		COMMON(IServer)
		INTERFACE(IServer)
		IMPL(mc::APImpl)
	END_INTERFACE_MAP()		

	// IServer section
	mc::result Server::AsyncAccept(short port)
	{
		if ( acceptor_ )
			return mc::_E_FAIL;

		acceptor_ = AcceptorPtr_(new Acceptor_(service(), asio::ip::tcp::endpoint(asio::ip::tcp::v4(), port)));

		Session::ptr_ new_session(new Session(service()));
		acceptor_->async_accept(new_session->socket(),
			boost::bind(&Server::HandleAccept, this, new_session, asio::placeholders::error));		

		return mc::_S_OK;
	}

	mc::result Server::AsyncAccept(const mc::StringA& port)
	{
		std::stringstream converter;
		converter << port;
		short port_short = 0;
		converter >> port_short;

		return AsyncAccept(port_short);
	}

	void Server::Run()
	{
		service().run();
	}

	void Server::Stop()
	{
		service().stop();
	}

	// Async handlers
	void Server::HandleAccept(Session::ptr_ new_session, const asio::error_code& error)
	{
		if ( error )
			return;

		// Notify subscribers on new connection
		IClientPtr client(mc::ObjectCreator< Client >(new_session), IID_IClient);	
		OnAccept(client);

		// Get ready for new connection
		new_session.reset(new Session(service()));
		acceptor_->async_accept(new_session->socket(),
			boost::bind(&Server::HandleAccept, this, new_session, asio::placeholders::error));		
	}

	// Event dispatchers	
	mc::result Server::OnAccept(IClientRef client)
	{
		return mc::APImpl::SpreadBase(
			AGENTID_ACCEPT, 
			mc::CreateParams(
				mc::ItemImpl::GetLocal(),					// Param1: Server
				client));									// Param2: Accepted client
	}

	// External tools
	IServerPtr InstantiateServer()
	{
		return IServerPtr(mc::ObjectCreator< Server >(), IID_IServer);
	}

}
