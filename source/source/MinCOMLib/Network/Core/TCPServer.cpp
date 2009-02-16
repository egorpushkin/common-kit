#include "Common/Common.h"

#include "TCPServer.h"

#include "Service.h"

namespace MinCOM
{

	TCPServer::TCPServer(IServiceRef service)
		: mc::CommonImpl< IServer >()
		, mc::APImpl()
		, service_( service )
		, acceptor_()
		, events_()
	{
	}

	// IServer section
	//////////////////////////////////////////////////////////////////////////

	mc::result TCPServer::AsyncAccept(const std::string& service)
	{
		if ( acceptor_ )
			return mc::_E_ALREADYINIT;

		std::stringstream converter;
		converter << service;
		short portShort = 0;
		converter >> portShort;

		acceptor_ = AcceptorPtr_( new Acceptor_( 
			Strong< Service >(service_)->GetService(), 
			boost::asio::ip::tcp::endpoint(boost::asio::ip::tcp::v4(), portShort)) );

		TCPConnection::SocketPtr_ socket( 
			new TCPConnection::Socket_( Strong< Service >(service_)->GetService() ) );
		acceptor_->async_accept(*socket,
			boost::bind(&TCPServer::HandleAccept, this, socket, boost::asio::placeholders::error));		

		return mc::_S_OK;
	}

	void TCPServer::Run()
	{
		service_->Run();
	}

	void TCPServer::Stop()
	{
		// TODO: Stop accepting connections and perform cleanup (acceptor_).
		service_->Stop();
	}

	// ICommon section
	//////////////////////////////////////////////////////////////////////////

	result TCPServer::PostInit()
	{
		// Register additional access point for events' delivery and configure 
		// events spreader.
		events_ = APImpl::AdviseAndThrow( TypeInfo< DServer >::GetGuid() );
		return _S_OK;
	}

	// Async handlers
	//////////////////////////////////////////////////////////////////////////

	void TCPServer::HandleAccept(TCPConnection::SocketPtr_ socket, const boost::system::error_code& error)
	{
		if ( error )
		{
			// TODO: Handle error correctly.
			return;
		}

		// Notify subscribers on new connection
		IConnectionPtr connection( mc::Class< TCPConnection >::Create( service_, socket ) );	
		events_->ConnectionAccepted(connection);

		// Get ready for new connection
		socket.reset( 
			new TCPConnection::Socket_( Strong< Service >(service_)->GetService() ) );
		acceptor_->async_accept(*socket,
			boost::bind(&TCPServer::HandleAccept, this, socket, boost::asio::placeholders::error));		
	}

}
