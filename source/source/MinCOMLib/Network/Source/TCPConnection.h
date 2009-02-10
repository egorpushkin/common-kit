#ifndef TCPCONNECTION_H__MINCOMLIB__INCLUDED_
#define TCPCONNECTION_H__MINCOMLIB__INCLUDED_

namespace MinCOM
{

	class TCPConnection
		: public CommonImpl< IConnection >
		, public APImpl
	{
	public:

		TCPConnection(IServiceRef service);

		// ITCPConnection section
		//////////////////////////////////////////////////////////////////////////

		virtual result Establish(const std::string& host, const std::string& service);

		virtual result Establish(IHostRef host);

		virtual void TCPConnection::ReadAsync(std::size_t minimum = 1);

		virtual std::streambuf& GetStream();

		// ICommon section
		//////////////////////////////////////////////////////////////////////////

		/**
		 * Overridden to init events spreader.
		 */
		virtual result PostInit();

	private:

		/**
		 * This callback is passed to ASIO internals and is called 
		 * when data is arrived.
		 */ 
		void HandleRead(const boost::system::error_code& error);

	private:

		/**
		 * Typedef for socket entity to be used inbound of the class.
		 */ 
		typedef boost::asio::ip::tcp::socket Socket_;

	private:

		/** . */
		IServicePtr service_;

		/** . */
		Socket_ socket_;

		/** Buffer to hold received data. */
		boost::asio::streambuf buffer_;

		/** Connection events spreader. */
		DRawDataPtr events_;
	};

}

#endif // !TCPCONNECTION_H__MINCOMLIB__INCLUDED_