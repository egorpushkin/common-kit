#ifndef IHOST_H__NETWORK__COMMONKIT__INCLUDED_
#define IHOST_H__NETWORK__COMMONKIT__INCLUDED_

namespace Network
{

	interface IHost : public mc::ICommon
	{

		virtual mc::StringA GetHost() = 0;

		virtual mc::StringA GetPort() = 0;

	};

	typedef mc::ComPtr< IHost > IHostPtr;
	typedef const IHostPtr& IHostRef;

	// {a59cd1a9-28ce-46f3-8cb5-ce28d5f2bedc} 
	MC_DEFINE_GUID(IID_IHost, 
	0xa59cd1a9, 0x28ce, 0x46f3, 0x8c, 0xb5, 0xce, 0x28, 0xd5, 0xf2, 0xbe, 0xdc);

}

#endif // !IHOST_H__NETWORK__COMMONKIT__INCLUDED_
