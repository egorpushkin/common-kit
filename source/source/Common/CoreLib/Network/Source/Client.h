#ifndef CLIENT_H__NETWORK__CORELIB__INCLUDED_
#define CLIENT_H__NETWORK__CORELIB__INCLUDED_

namespace Network
{

	class Client 
		: public mc::CommonImpl< IClient >
		, public mc::APImpl
	{
	public:

		Client();

		Client(const Session::ptr_& session);

		// ICommon section
		DECLARE_INTERFACE_MAP()		

		// IClient section
		virtual mc::result Connect(IHostRef host);

		virtual mc::result Write(asio::streambuf& buffer);

		virtual std::size_t Read(const mc::StringA& delimiter);

		virtual std::size_t Read(std::size_t minimum = 1);

		virtual void AsyncRead(std::size_t minimum = 1);

		virtual asio::streambuf& GetBuffer();

	private:

		// Async handlers
		void HandleRead(const asio::error_code& error);

		// Event dispatchers	
		mc::result OnData();

	private:

		Session::ptr_ session_;

		asio::streambuf buffer_;

	};

}

#endif // !CLIENT_H__NETWORK__CORELIB__INCLUDED_
