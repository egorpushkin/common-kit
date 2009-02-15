#include "Common/Common.h"

#include "TCPConnection.h"

#include "Service.h"

namespace MinCOM
{

	TCPConnection::TCPConnection(IServiceRef service)
		: mc::CommonImpl< IConnection >()
		, mc::APImpl()
		, service_(service)
		, socket_( Strong< Service >(service_)->GetService() )
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
				socket_.close();
				socket_.connect(*endpointIterator++, error);
			}

			if ( error )
				return mc::_E_FAIL;
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
			socket_, 
			ibuffer_, 
			boost::asio::transfer_at_least(minimum),
			boost::bind(&TCPConnection::HandleRead, this, boost::asio::placeholders::error));
	}

	void TCPConnection::Write()
	{
		boost::asio::write(
			socket_, 
			obuffer_,
			boost::asio::transfer_all()); 
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
		events_ = APImpl::Advise( TypeInfo< DRawData >::GetGuid() );
		return _S_OK;
	}

	// Async handlers
	//////////////////////////////////////////////////////////////////////////

	void TCPConnection::HandleRead(const boost::system::error_code& error)
	{
		if ( error )
		{
			// TODO: Handle this situation correctly.
			// This cause is potentially influenced by disconnection.
			// All local references should be NULLed and corresponding 
			// (DRawData->Disconnected) event should be spread.
			return;
		}
		
		// Spread event to subscribers.
		events_->DataReceived( CommonImpl< IConnection >::GetSelf() );		
	}

	void a()
	{
		boost::asio::streambuf s;

		std::stringbuf ss;


	}
	
	// IClient section
	/* mc::result Client::Write(asio::streambuf& buffer)
	{
		asio::write(
			session_->socket(), 
			buffer);

		return mc::_S_OK;
	}

	std::size_t Client::Read(const mc::StringA& delimiter)
	{
		asio::error_code error = asio::error::bad_descriptor;
		std::size_t actually_read = asio::read_until(
			session_->socket(), 
			buffer_,
			delimiter, 
			error);

		if ( error )
			return 0;

		return actually_read;
	}

	std::size_t Client::Read(std::size_t minimum)
	{
		asio::error_code error = asio::error::bad_descriptor;
		std::size_t actually_read = asio::read(
			session_->socket(), 
			buffer_,
			asio::transfer_at_least(minimum), 
			error);

		if ( error )
			return 0;

		return actually_read;
	} */

}
