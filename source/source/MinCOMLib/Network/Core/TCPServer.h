#ifndef TCPSERVER_H__MINCOMLIB__INCLUDED_
#define TCPSERVER_H__MINCOMLIB__INCLUDED_

#include "TCPConnection.h"

namespace MinCOM
{

	class TCPServer 
		: public mc::CommonImpl< IServer >
		, public mc::APImpl
	{
	public:

		TCPServer(IServiceRef service);

		// IServer section
		virtual result AsyncAccept(const std::string& service);

		virtual void Run();

		virtual void Stop();

		// ICommon section
		virtual result PostInit();

	private:

		// Async handlers
		void HandleAccept(TCPConnection::SocketPtr_ socket, const boost::system::error_code& error);

	private:

		typedef boost::asio::ip::tcp::acceptor Acceptor_;

		typedef boost::shared_ptr< Acceptor_ > AcceptorPtr_;

	private:

		/** . */
		IServicePtr service_;

		/** . */
		AcceptorPtr_ acceptor_;

		/** . */
		DServerPtr events_;

	};

}

#endif // !TCPSERVER_H__MINCOMLIB__INCLUDED_
