#ifndef INSTRESPMSG_H__REMOTING__CORELIB__INCLUDED_
#define INSTRESPMSG_H__REMOTING__CORELIB__INCLUDED_

namespace Remoting
{

	class InstRespMsg
		: public Network::MessageImpl
	{
	public:

		InstRespMsg();

		InstRespMsg(Network::IClient::Id_ id, mc::result respose);

		// IMessage section
		virtual Network::IMessage::Size_ GetDataSize();

		// MessageImpl section
		virtual mc::result WriteBody(std::ostream& stream);

		virtual mc::result ReadBody(std::istream& stream);

	};

}

#endif // !INSTRESPMSG_H__REMOTING__CORELIB__INCLUDED_
