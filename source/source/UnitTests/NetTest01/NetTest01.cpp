// NetTest01.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include <wchar.h>

class DataReceiver
	: public mc::CommonImpl< mc::DRawData >
{
public:

	// DRawData section
	virtual mc::result Connected(mc::IConnectionRef connection)
	{
		std::cout << "Connected!" << std::endl;

		std::string url("/");
		std::string host("www.google.com");

		std::ostream request_stream(&connection->GetOStreamBuf());
		request_stream << "GET " << url << " HTTP/1.0\r\n";
		request_stream << "Host: " << host << "\r\n";
		request_stream << "Accept: */*\r\n";
		request_stream << "Connection: close\r\n\r\n";

		connection->Write();

		connection->ReadAsync(1);

		return mc::_S_OK;
	}

	virtual mc::result DataReceived(mc::IConnectionRef connection)
	{
		std::string data_buffer;
		std::istream data_stream(&connection->GetIStreamBuf());

		std::getline(data_stream, data_buffer, '\x0');
		
		std::cout << data_buffer << std::endl;

		connection->ReadAsync();

		return mc::_S_OK;
	}

	virtual mc::result Disconnected(mc::IConnectionRef connection)
	{
		std::cout << "Disconnected!" << std::endl;

		mc::result code = connection->Establish("google.com", "80");

		return mc::_S_OK;
	}


};

class Thread
	: public mc::CommonImpl< mc::IRunnable >
{
public:

	Thread(mc::IServiceRef service)
		: service_(service)
	{
	}

	// IRunnable section
	virtual mc::result Run()
	{		
		service_->Run();

		return mc::_S_OK;
	}

private:

	mc::IServicePtr service_;

};


int _tmain(int /* argc */, _TCHAR* /* argv[] */)
{

	try
	{
		
		mc::IServicePtr service = mc::Library::Service();
		mc::IConnectionPtr connection = mc::Library::TCPConnection(service);
		connection->Establish("localhost", "8444");

		_getwch();

		/* mc::ICommonPtr dataReceiver( mc::Class< DataReceiver >::Create() );
		mc::Events::Advise(connection, dataReceiver, mc::TypeInfo< mc::DRawData >::GetGuid() );


		mc::result code = connection->Establish("google.com", "80");
		if ( mc::Error::IsSucceeded( code ) )
		{
			std::cout << "Connected!";
		}
		else
		{
			std::cout << "Failed to connect!";	
			return 0;
		} 

		// service->Work();
		for ( ;; )
		{
			// service->Work();
			service->Run();
		} */

		// mc::IThread::Sleep(100*1000);


	}
	catch ( std::exception& e )
	{
		std::cout << "Exception: " << e.what() << "\n";
	}

	return 0;
}

