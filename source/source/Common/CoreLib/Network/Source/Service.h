#ifndef SERVICE_H__NETWORK__CORELIB__INCLUDED_
#define SERVICE_H__NETWORK__CORELIB__INCLUDED_

namespace Network
{

	class Service 
		: public boost::noncopyable
	{
	public:

		asio::io_service& service();

	private:

		asio::io_service service_;

	};

	typedef Loki::SingletonHolder< Service > ServiceHolder;

	asio::io_service& service();

}

#endif // !SERVICE_H__NETWORK__CORELIB__INCLUDED_
