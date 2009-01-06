#ifndef ISERVER_H__REMOTING__COMMONKIT__INCLUDED_
#define ISERVER_H__REMOTING__COMMONKIT__INCLUDED_

namespace Remoting
{

	interface IServer : public mc::ICommon
	{

		virtual mc::result Run(Network::IHostRef host) = 0;

	};

	typedef mc::ComPtr< IServer > IServerPtr;
	typedef const IServerPtr& IServerRef;

	// {baa51543-83fc-48eb-81e8-77480c978660} 
	MC_DEFINE_GUID(IID_IServer, 
	0xbaa51543, 0x83fc, 0x48eb, 0x81, 0xe8, 0x77, 0x48, 0x0c, 0x97, 0x86, 0x60);

	IServerPtr InstantiateServer();

}

#endif // !IMACHINE_H__REMOTING__COMMONKIT__INCLUDED_
