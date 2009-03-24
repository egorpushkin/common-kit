#include "Common/Common.h"

#include "TCPConnection.h"

#include "Service.h"

#include "HandlerWrapper.h"

namespace MinCOM
{

	TCPConnection::TCPConnection(IServiceRef service)
		: mc::CommonImpl< IConnection >()
		, mc::APImpl()
		, service_( service )
		, socket_( new Socket_( Strong< Service >(service_)->GetService() ) )
		, state_(NOT_INITIALIZED)
		, ibuffer_()
		, obuffer_()
		, events_()
	{
		if ( !service ) throw std::exception();
	}

	TCPConnection::TCPConnection(IServiceRef service, const SocketPtr_& socket)
		: mc::CommonImpl< IConnection >()
		, mc::APImpl()
		, service_( service )
		, socket_( socket )
		, state_(CONNECTED)
		, ibuffer_()
		, obuffer_()
		, events_()
	{
		if ( !service ) throw std::exception();
		if ( !socket ) throw std::exception();
		// TODO: Check whether socket is ok (using probably is_open()).
	}

	TCPConnection::~TCPConnection()
	{
		socket_->close();
	}

	// ITCPConnection section
	//////////////////////////////////////////////////////////////////////////

	result TCPConnection::Establish(const std::string& host, const std::string& service)
	{
        MC_LOG_ROUTINE;
		CoreMutexLock locker(CommonImpl< IConnection >::GetLock());

		// There is a problem with maintaining connection state after reconnect
		// (it is synchronously set to CONNECTED and later asynchronously 
		// returned back to DISCONNECTED by handler (read or write) which is
		// related to previous connection. 
		// TODO: Fix this problem and make it possible to reconnect.
		if ( ( NOT_INITIALIZED != state_ ) && ( DISCONNECTED != state_ ) )
			return mc::_E_ALREADYINIT;
		
		try
		{
			state_ = CONNECTING;

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

			// Check whether connection attempt failed.
			if ( error )
			{
				// Modify state. 
				state_ = DISCONNECTED;
				return mc::_E_FAIL;
			}

			// Modify state.
			state_ = CONNECTED;

			// Spread good news.
			events_->Connected( CommonImpl< IConnection >::GetSelf() );

			// Make this object immortal.
			self_ = CommonImpl< IConnection >::GetSelf();
		}
		catch( ... )
		{
			state_ = DISCONNECTED;
			return mc::_E_FAIL;
		}

		return mc::_S_OK;
	}

	result TCPConnection::Establish(IHostRef host)
	{
		return Establish(host->GetHost(), host->GetService());
	}
    
    result TCPConnection::Close()
    {
		MC_LOG_ROUTINE;
		CoreMutexLock locker(CommonImpl< IConnection >::GetLock());
        if ( CONNECTED != state_ )
            return _E_NOTINIT;
        // Break the connection.
		try
		{
			socket_->close();        
		}
		catch ( ... ) 
		{			
		}
		// TODO: Check that connection should not be turned into DISCONNECTED
		// state here. 
        return _S_OK;
    }

	IConnection::State_ TCPConnection::GetState()
	{
		return state_;
	}

	std::string TCPConnection::GetIpAddress()
	{
		MC_LOG_ROUTINE;
		CoreMutexLock locker(CommonImpl< IConnection >::GetLock());
		if ( CONNECTED != state_ )
			return std::string();
		return socket_->remote_endpoint().address().to_string();
	}

	void TCPConnection::ReadAsync(std::size_t minimum)
	{
		MC_LOG_ROUTINE;
		CoreMutexLock locker(CommonImpl< IConnection >::GetLock());
		if ( CONNECTED != state_ )
			return;
		try
		{
			boost::asio::async_read(
				*socket_, 
				ibuffer_, 
				boost::asio::transfer_at_least(minimum),
				boost::bind(
					&TCPConnection::HandleRead, 
					// This helps to maintain lifetime of this (TCPConnection) 
					// object independently from client application architecture.
					HandlerWrapper< TCPConnection >::Ptr_( new HandlerWrapper< TCPConnection >(this, CommonImpl< IConnection >::GetSelf()) ),
					boost::asio::placeholders::error));
		}
		catch ( ... )
		{
			// Error should be handled here because is may occur so that there 
			// are no any registered handlers at the moment. 
			HandleDisconnectionInIOServiceThread();
		}
	}

	void TCPConnection::WriteAsync()
	{
		MC_LOG_ROUTINE;
		CoreMutexLock locker(CommonImpl< IConnection >::GetLock());
		if ( CONNECTED != state_ )
			return;
		try
		{
			boost::asio::async_write(
				*socket_, 
				obuffer_,
				boost::asio::transfer_all(),            
				boost::bind(
					&TCPConnection::HandleWrite, 
					// This helps to maintain lifetime of this (TCPConnection) 
					// object independently from client application architecture.
					HandlerWrapper< TCPConnection >::Ptr_( new HandlerWrapper< TCPConnection >(this, CommonImpl< IConnection >::GetSelf()) ),
					boost::asio::placeholders::error)); 
		}
		catch ( ... )
		{
			// Error should be handled here because is may occur so that there 
			// are no any registered handlers at the moment. 
			HandleDisconnectionInIOServiceThread();
		}
	}
    
    void TCPConnection::Write()   
    {
		MC_LOG_ROUTINE;
		if ( CONNECTED != state_ )
			return;
		try
		{
			boost::asio::write(
               *socket_, 
               obuffer_,
               boost::asio::transfer_all());
		}
		catch ( ... )
		{
			// Error should be handled here because is may occur so that there 
			// are no any registered handlers at the moment. 
			HandleDisconnectionInIOServiceThread();
		}        
    }

	std::streambuf& TCPConnection::GetIStreamBuf()
	{
		return ibuffer_;
	}

	size_t TCPConnection::GetISize()
	{
		return ibuffer_.size();
	}

	std::streambuf& TCPConnection::GetOStreamBuf()
	{
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
	void TCPConnection::HandleWrite(const boost::system::error_code& error)
	{
		MC_LOG_ROUTINE;
		CoreMutexLock locker(CommonImpl< IConnection >::GetLock());
		if ( !HandleError(error) )
		{
			// Error was detected, handled and dispatched. Required cleanup 
			// was also performed. So.. nothing else should be done here.
			return;
		}
	}

	void TCPConnection::HandleRead(const boost::system::error_code& error)
	{
		MC_LOG_ROUTINE;
		CoreMutexLock locker(CommonImpl< IConnection >::GetLock());        
		if ( !HandleError(error) )
		{
			// Error was detected, handled and dispatched. Required cleanup 
			// was also performed. So.. nothing else should be done here.
			return;
		}

		// Spread event to subscribers.
		events_->DataReceived( CommonImpl< IConnection >::GetSelf() );		
        
		// Continue asynchronous reading.
        ReadAsync();        
	}

	// Internal helpers
	//////////////////////////////////////////////////////////////////////////

	bool TCPConnection::HandleError(const boost::system::error_code& error)
	{
		MC_LOG_ROUTINE;
		if ( error && boost::asio::error::operation_aborted != error )
		{
			MC_LOG_STATEMENT("Error has occurred");
			if ( DISCONNECTED == state_ )
				return false;
			
			// There is no need to dispatch this handler by io_service because 
			// 'HandleError' method may only be called from another handler. 
			HandleDisconnection();
			return false;
		}		

		return true;
	}

	void TCPConnection::HandleDisconnectionInIOServiceThread()
	{
		MC_LOG_ROUTINE;
		Strong< Service >(service_)->GetService().dispatch(
			boost::bind(
				&TCPConnection::HandleDisconnection,
				HandlerWrapper< TCPConnection >::Ptr_( 
					new HandlerWrapper< TCPConnection >(this, CommonImpl< IConnection >::GetSelf() )
				) 
			) 
		);
	}

	void TCPConnection::HandleDisconnection() 
	{
		MC_LOG_ROUTINE;
		// Modify connection state.
		state_ = DISCONNECTED;
		// Connection closed cleanly by peer.
		events_->Disconnected( CommonImpl< IConnection >::GetSelf() );
		// Close socket.
		socket_->close();		
	}

}

