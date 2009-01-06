#ifndef LOCALHOST_H__NETWORK__COMMONKIT__INCLUDED_
#define LOCALHOST_H__NETWORK__COMMONKIT__INCLUDED_

namespace Network
{

	class Localhost 
		: public HostImpl 
	{
	public:

		Localhost();

		Localhost(const mc::StringA& port);

	};

}

#endif // !LOCALHOST_H__NETWORK__COMMONKIT__INCLUDED_
