#include "Common/Common.h"

#include "TCPConnection.h"

#include "Service.h"

namespace MinCOM
{

	TCPConnection::TCPConnection(IServiceRef service)
		: mc::CommonImpl< IConnection >()
		, mc::APImpl()
		, service_( service )
		, socket_( new Socket_( Strong< Service >(service_)->GetService() ) )
		, ibuffer_()
		, obuffer_()
		, events_()
	{
	}

	TCPConnection::TCPConnection(IServiceRef service, const SocketPtr_& socket)
		: mc::CommonImpl< IConnection >()
		, mc::APImpl()
		, service_( service )
		, socket_( socket )
		, ibuffer_()
		, obuffer_()
		, events_()
	{
	}

	// ITCPConnection section
	//////////////////////////////////////////////////////////////////////////

	result TCPConnection::Establish(const std::string& host, const std::string& service)
	{
		CoreMutexLock locker(CommonImpl< IConnection >::GetLock());

		try
		{
			// Flush buffers.
			ibuffer_.consume(ibuffer_.size());
			obuffer_.consume(obuffer_.size());

			// Establish new one.
			boost::asio::ip::tcp::resolver resolver(Strong< Service >(service_)->GetService());
			boost::asio::ip::tcp::resolver::query query(host, service);
			boost::asio::ip::tcp::resolver::iterator endpointIterator = resolver.resolve(query);
			boost::asio::ip::tcp::resolver::iterator end;

			// Try each endpoint until we successfully establish a connection.
			boost::system::error_code error = boost::asio::error::host_not_found;
			while ( error && endpointIterator != end )
			{
				socket_->close();
				socket_->connect(*endpointIterator++, error);
			}

			if ( error )
				return mc::_E_FAIL;

			// Spread good news.
			events_->Connected( CommonImpl< IConnection >::GetSelf() );
		}
		catch( ... )
		{
			return mc::_E_FAIL;
		}

		return mc::_S_OK;
	}

	result TCPConnection::Establish(IHostRef host)
	{
		return Establish(host->GetHost(), host->GetService());
	}

	void TCPConnection::ReadAsync(std::size_t minimum)
	{
		CoreMutexLock locker(CommonImpl< IConnection >::GetLock());

		boost::asio::async_read(
			*socket_, 
			ibuffer_, 
			boost::asio::transfer_at_least(minimum),
			boost::bind(&TCPConnection::HandleRead, this, boost::asio::placeholders::error));
	}

	void TCPConnection::Write()
	{
		boost::system::error_code error;
		boost::asio::write(
			*socket_, 
			obuffer_,
			boost::asio::transfer_all(),
			error);

		HandleError(error);
		// There is no sense to handle return value. This routine should exit 
		// in any case.
	}

	std::streambuf& TCPConnection::GetIStreamBuf()
	{
		CoreMutexLock locker(CommonImpl< IConnection >::GetLock());
		return ibuffer_;
	}

	size_t TCPConnection::GetISize()
	{
		return ibuffer_.size();
	}

	std::streambuf& TCPConnection::GetOStreamBuf()
	{
		CoreMutexLock locker(CommonImpl< IConnection >::GetLock());
		return obuffer_;
	}

	size_t TCPConnection::GetOSize()
	{
		return obuffer_.size();
	}

	// ICommon section
	//////////////////////////////////////////////////////////////////////////

	result TCPConnection::PostInit()
	{
		// Register additional access point for events' delivery and configure 
		// events spreader.
		events_ = APImpl::AdviseAndThrow( TypeInfo< DRawData >::GetGuid() );
		return _S_OK;
	}

	// Async handlers
	//////////////////////////////////////////////////////////////////////////

	void TCPConnection::HandleRead(const boost::system::error_code& error)
	{
		if ( !HandleError(error) )
		{
			// Error was detected, handled and dispatched. Required cleanup 
			// was also performed. So.. nothing else should be done here.
			return;
		}
		
		// Spread event to subscribers.
		events_->DataReceived( CommonImpl< IConnection >::GetSelf() );		
	}

	// Internal helpers
	//////////////////////////////////////////////////////////////////////////

	bool TCPConnection::HandleError(const boost::system::error_code& error)
	{
		if ( boost::asio::error::eof == error )
		{
			// Connection closed cleanly by peer.
			events_->Disconnected( CommonImpl< IConnection >::GetSelf() );
			return false;
		}
		else if ( error )
		{
			// Some other error occured.
			events_->Disconnected( CommonImpl< IConnection >::GetSelf() );
			return false;
		}		

		return true;
	}

}
