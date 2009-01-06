#ifndef ICLIENT_H__NETWORK__COMMONKIT__INCLUDED_
#define ICLIENT_H__NETWORK__COMMONKIT__INCLUDED_

namespace Network
{

	interface IClient : public mc::ICommon
	{

		typedef unsigned long Id_;

		virtual mc::result Connect(IHostRef host) = 0;

		virtual mc::result Write(asio::streambuf& buffer) = 0;

		virtual std::size_t Read(const mc::StringA& delimiter) = 0;

		virtual std::size_t Read(std::size_t minimum = 1) = 0;

		virtual void AsyncRead(std::size_t minimum = 1) = 0;

		virtual asio::streambuf& GetBuffer() = 0;

	};

	typedef mc::ComPtr< IClient > IClientPtr;
	typedef const IClientPtr& IClientRef;

	// {2464e7c4-fac7-43bb-a104-75b1baeb833d} 
	MC_DEFINE_GUID(IID_IClient, 
	0x2464e7c4, 0xfac7, 0x43bb, 0xa1, 0x04, 0x75, 0xb1, 0xba, 0xeb, 0x83, 0x3d);

	typedef enum tagClientEvents
	{

		AGENTID_DATA = 0xff010E01

	}
	ClientEvents;

	IClientPtr InstantiateClient();

}

#endif // !ICLIENT_H__NETWORK__COMMONKIT__INCLUDED_
