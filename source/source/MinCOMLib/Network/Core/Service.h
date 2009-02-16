#ifndef SERVICE_H__MINCOMLIB__INCLUDED_
#define SERVICE_H__MINCOMLIB__INCLUDED_

namespace MinCOM
{

	class Service 
		: public CommonImpl< IService >
	{
	public:

		Service();

		// IService section
		virtual void Run();

		virtual void Stop();

	protected:

		friend class TCPConnection;
		friend class TCPServer;

		boost::asio::io_service& GetService();

	private:

		boost::asio::io_service service_;

	};

}

#endif // !SERVICE_H__MINCOMLIB__INCLUDED_
