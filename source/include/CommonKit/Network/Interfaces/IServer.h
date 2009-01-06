#ifndef ISERVER_H__NETWORK__COMMONKIT__INCLUDED_
#define ISERVER_H__NETWORK__COMMONKIT__INCLUDED_

namespace Network
{

	interface IServer : public mc::ICommon
	{
		
		virtual mc::result AsyncAccept(short port) = 0;

		virtual mc::result AsyncAccept(const mc::StringA& port) = 0;

		virtual void Run() = 0;

		virtual void Stop() = 0;

	};

	typedef mc::ComPtr< IServer > IServerPtr;
	typedef const IServerPtr& IServerRef;

	// {871a153d-b6d2-4851-8275-81c1ae41a4dd} 
	MC_DEFINE_GUID(IID_IServer, 
	0x871a153d, 0xb6d2, 0x4851, 0x82, 0x75, 0x81, 0xc1, 0xae, 0x41, 0xa4, 0xdd);

	typedef enum tagServerEvents
	{

		AGENTID_ACCEPT = 0xff010D01,

	}
	ServerEvents;

	IServerPtr InstantiateServer();

}

#endif // !ISERVER_H__NETWORK__COMMONKIT__INCLUDED_
