#ifndef TCPCONNECTION_H__MINCOMLIB__INCLUDED_
#define TCPCONNECTION_H__MINCOMLIB__INCLUDED_

namespace MinCOM
{

	class TCPConnection
		: public CommonImpl< IConnection >
		, public APImpl
	{
    public:

		typedef CommonImpl< IConnection > ClassRoot_;

		/**
	 	 * Typedef for socket entity to be used by classes from TCP family.
		 */ 
		typedef boost::asio::ip::tcp::socket Socket_;

		/**
		 * Pointer wrapping TCP socket.
		 */ 
		typedef boost::shared_ptr< Socket_ > SocketPtr_;

    public:

		TCPConnection(IServiceRef service);

		TCPConnection(IServiceRef service, const SocketPtr_& socket);

		virtual ~TCPConnection();

		// ITCPConnection section
		//////////////////////////////////////////////////////////////////////////

		virtual result Establish(const std::string& host, const std::string& service);

		virtual result Establish(IHostRef host);

		virtual std::string GetIpAddress();

		virtual void TCPConnection::ReadAsync(std::size_t minimum = 1);

		virtual void WriteAsync();

		virtual std::streambuf& GetIStreamBuf();

		virtual size_t GetISize();

		virtual std::streambuf& GetOStreamBuf();

		virtual size_t GetOSize();

		// ICommon section
		//////////////////////////////////////////////////////////////////////////

		/**
		 * Overridden to init events spreader.
		 */
		virtual result PostInit();

	private:

		/**
		 * This callback is passed to ASIO internals and is called 
		 * when data is sent.
		 */ 
		void HandleWrite(const boost::system::error_code& error);

		/**
		 * This callback is passed to ASIO internals and is called 
		 * when data is arrived.
		 */ 
		void HandleRead(const boost::system::error_code& error);

	protected:

		/**
		 * Handles error correctly. 
		 * Performs required cleanup of the TCPConnection entry and
		 * dispatches corresponding events to subscribers.
		 *
		 * @return Returns false if error has occurred.
		 */
		bool HandleError(const boost::system::error_code& error);
        
	private:
        
		/** . */
		IServicePtr service_;

		/** . */
		SocketPtr_ socket_;

		/** Buffer to hold received data. */
		boost::asio::streambuf ibuffer_;

		/** Buffer to hold data to be sent. */
		boost::asio::streambuf obuffer_;
        
		/** Connection events spreader. */
		DRawDataPtr events_;

	};
    
}

#endif // !TCPCONNECTION_H__MINCOMLIB__INCLUDED_
