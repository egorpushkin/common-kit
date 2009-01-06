#include "Common/Common.h"

#include "CommonKit/Network.h"

#include "Session.h"

#include "Client.h"

#include "Service.h"

namespace Network
{

	Client::Client()
		: mc::CommonImpl< IClient >()
		, mc::APImpl()
		, session_(new Session(service()))
		, buffer_()
	{
	}

	Client::Client(const Session::ptr_& session)
		: mc::CommonImpl< IClient >()
		, mc::APImpl()
		, session_(session)
	{		
	}

	// ICommon section
	BEGIN_INTERFACE_MAP(Client)
		COMMON(IClient)
		INTERFACE(IClient)
		IMPL(mc::APImpl)
	END_INTERFACE_MAP()		

	// IClient section
	mc::result Client::Connect(IHostRef host)
	{
		try
		{
			session_->socket().close();

			asio::ip::tcp::resolver resolver(service());
			asio::ip::tcp::resolver::query query(host->GetHost(), host->GetPort());
			asio::ip::tcp::resolver::iterator endpoint_iterator = resolver.resolve(query);
			asio::ip::tcp::resolver::iterator end;

			// Try each endpoint until we successfully establish a connection.
			asio::error_code error = asio::error::host_not_found;
			while ( error && endpoint_iterator != end )
			{
				session_->socket().close();
				session_->socket().connect(*endpoint_iterator++, error);
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

	mc::result Client::Write(asio::streambuf& buffer)
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
	}

	void Client::AsyncRead(std::size_t minimum)
	{
/*		std::size_t actually_read = Read(0);
		if ( actually_read > 0 )
			OnData();*/

		asio::async_read(
			session_->socket(), 
			buffer_, 
			asio::transfer_at_least(minimum),
			boost::bind(&Client::HandleRead, this, asio::placeholders::error));
	}

	asio::streambuf& Client::GetBuffer()
	{
		return buffer_;
	}

	// Async handlers
	void Client::HandleRead(const asio::error_code& error)
	{
		if ( error )
			return;

		OnData();		
	}

	// Event dispatchers	
	mc::result Client::OnData()
	{
		return mc::APImpl::SpreadBase(
			AGENTID_DATA, 
			mc::CreateParams(
				mc::ItemImpl::GetLocal()));	// Param1: Client
	}

	// External tools
	IClientPtr InstantiateClient()
	{
		return IClientPtr(mc::ObjectCreator< Client >(), IID_IClient);
	}

}
