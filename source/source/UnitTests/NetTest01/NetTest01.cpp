// NetTest01.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

class DataReceiver
	: public mc::CommonImpl< mc::DRawData >
{
public:

	// DRawData section
	virtual mc::result Connected(mc::IConnectionRef connection)
	{
		return mc::_S_OK;
	}

	virtual mc::result DataReceived(mc::IConnectionRef connection)
	{
		

		return mc::_S_OK;
	}

	virtual mc::result Disconnected(mc::IConnectionRef connection)
	{
		return mc::_S_OK;
	}


protected:
private:
};


int _tmain(int /* argc */, _TCHAR* /* argv[] */)
{

	try
	{
		
		mc::IServicePtr service = mc::Library::Service();

		mc::IConnectionPtr connection = mc::Library::TCPConnection(service);

		mc::result code = connection->Establish("localhost", "80");
		if ( mc::Error::IsSucceeded( code ) )
		{
			std::cout << "Connected!";
		}

		
		mc::ICommonPtr dataReceiver( mc::Class< DataReceiver >::Create() );
		mc::Events::Advise(connection, dataReceiver, mc::TypeInfo< mc::DRawData >::GetGuid() );


		connection->ReadAsync(1);


		service->Run();


	}
	catch ( std::exception& e )
	{
		std::cout << "Exception: " << e.what() << "\n";
	}

	return 0;
}

