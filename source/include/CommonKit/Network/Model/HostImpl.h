#ifndef HOSTIMPL_H__NETWORK__COMMONKIT__INCLUDED_
#define HOSTIMPL_H__NETWORK__COMMONKIT__INCLUDED_

namespace Network
{

	class HostImpl 
		: public mc::CommonImpl< IHost > 
	{
	public:

		HostImpl();

		HostImpl(const mc::StringA& host, bool defaultPort = false);

		HostImpl(const mc::StringA& host, const mc::StringA& port);

		// ICommon section
		DECLARE_INTERFACE_MAP()		

		// IHost section
		virtual mc::StringA GetHost();

		virtual mc::StringA GetPort();

	private:

		mc::StringA host_;

		mc::StringA port_;

	};

}

#endif // !HOSTIMPL_H__NETWORK__COMMONKIT__INCLUDED_
