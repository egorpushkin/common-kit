#ifndef SERVER_H__NETWORK__CORELIB__INCLUDED_
#define SERVER_H__NETWORK__CORELIB__INCLUDED_

namespace Network
{

	class Server 
		: public mc::CommonImpl< IServer >
		, public mc::APImpl
	{
	public:

		Server();

		// ICommon section
		DECLARE_INTERFACE_MAP()		

		// IServer section
		virtual mc::result AsyncAccept(short port);

		virtual mc::result AsyncAccept(const mc::StringA& port);

		virtual void Run();

		virtual void Stop();

	private:

		// Async handlers
		void HandleAccept(Session::ptr_ new_session, const asio::error_code& error);

		// Event dispatchers	
		mc::result OnAccept(IClientRef client);

	private:

		typedef asio::ip::tcp::acceptor Acceptor_;
		typedef boost::shared_ptr< Acceptor_ > AcceptorPtr_;

		AcceptorPtr_ acceptor_;

	};

}

#endif // !SERVER_H__NETWORK__CORELIB__INCLUDED_
