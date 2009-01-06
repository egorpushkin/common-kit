// NetTest01.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

class sync_http_helper
{
public:

	static Network::IClientPtr connect(const std::string& host, const std::string& port)
	{
		Network::IClientPtr client = Network::InstantiateClient();
		if ( !client )
			return NULL;

		if ( mc::IsFailed(client->Connect(host, port)) )
			return NULL;

		return client;
	}

	static void prepare_get_request(const std::string& host, const std::string& url, asio::streambuf& request)
	{
		std::ostream request_stream(&request);
		request_stream << "GET " << url << " HTTP/1.0\r\n";
		request_stream << "Host: " << host << "\r\n";
		request_stream << "Accept: */*\r\n";
		request_stream << "Connection: close\r\n\r\n";
	}

	static void skip_headers(Network::IClientRef client, asio::streambuf& response)
	{
		client->Read(response, "\r\n");
		std::size_t length = client->Read(response, "\r\n\r\n");
		response.consume(length);
	}

};

class sync_http_client
{
public:

	sync_http_client(const std::string& host, const std::string& port, const std::string& path)
	{
		Network::IClientPtr client = sync_http_helper::connect(host, port);
		if ( !client )
			throw asio::system_error(asio::error::connection_refused);

		asio::streambuf request;
		sync_http_helper::prepare_get_request(host, path, request);
		client->Write(request);

		sync_http_helper::skip_headers(client, response_);

		while ( client->Read(response_) );
	}

	std::istream get_data_stream()
	{
		return std::istream(&response_);
	}

	bool has_data()
	{
		return ( response_.size() > 0 );
	}

	std::string get_data()
	{
		std::string data_buffer;

		std::istream data_stream(&response_);
		std::getline(data_stream, data_buffer, '\x0');

		return data_buffer;
	}

private:

	asio::streambuf response_;

};

int _tmain(int /* argc */, _TCHAR* /* argv[] */)
{

	try
	{
		
		std::string host("localhost");
		std::string port("80");
		std::string path("/");

		sync_http_client client(host, port, path);
		std::cout << client.get_data();

/*
		std::string host("localhost");
		std::string port("80");
		std::string path("/joombla/");

		Network::IClientPtr client = sync_http_helper::connect(host, port);
		if ( !client )
			return -1;

		asio::streambuf request;
		sync_http_helper::prepare_get_request(host, path, request);
		client->Write(request);

		asio::streambuf response;
		sync_http_helper::skip_headers(client, response);

		while ( client->Read(response) )
		{
			std::cout << &response;			
		}	
*/

	}
	catch ( std::exception& e )
	{
		std::cout << "Exception: " << e.what() << "\n";
	}

	return 0;
}

