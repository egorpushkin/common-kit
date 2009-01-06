#ifndef SESSION_H__NETWORK__CORELIB__INCLUDED_
#define SESSION_H__NETWORK__CORELIB__INCLUDED_

namespace Network
{

	class Session 
		: public boost::enable_shared_from_this< Session >
	{
	
		typedef asio::ip::tcp::socket Socket_;

	public:

		typedef boost::shared_ptr< Session > ptr_;

		Session(asio::io_service& io_service);

		Socket_& socket();

	private:

		Socket_ socket_;

	};

}

#endif // !SESSION_H__NETWORK__CORELIB__INCLUDED_
