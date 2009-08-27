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
		// This value is hardcoded for now. In future it should be moved to
		// some kind of global config, with a chence to configure it even at
		// runtime.
		, attempts_(5)
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

		// Perform a number of attempts to start accepting connections.
		size_t attempt = 0;
		for ( attempt = 1 ; attempt <= attempts_ ; ++attempt )
		{
			try
			{
				acceptor_ = AcceptorPtr_( new Acceptor_(
					Strong< Service >(service_)->GetService(),
					boost::asio::ip::tcp::endpoint(boost::asio::ip::tcp::v4(),
					portShort),
					// Address should be reused.
					true) );
				break;
			}
			catch (...)
			{
				// This may occur if service is already in use.
				// Nothing shoould be done here. Just proceed to the next loop
				// iteration - next attempts to start server.
			}
		}
		if ( attempt > attempts_ )
		{
			// This occurs, if server has failed to start even after a number of
			// attempts.
			return _E_FAIL;
		}

		// Create accepting socket.
		TCPConnection::SocketPtr_ socket( 
			new TCPConnection::Socket_( Strong< Service >(service_)->GetService() ) );
		acceptor_->async_accept(*socket,
			boost::bind(&TCPServer::HandleAccept, this, socket, boost::asio::placeholders::error));		

		return _S_OK;
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
