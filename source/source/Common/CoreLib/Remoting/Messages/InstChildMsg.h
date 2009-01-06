#ifndef INSTCHILDMSG_H__REMOTING__CORELIB__INCLUDED_
#define INSTCHILDMSG_H__REMOTING__CORELIB__INCLUDED_

namespace Remoting
{

	class InstChildMsg
		: public Network::MessageImpl
	{
	public:

		InstChildMsg(Network::IMessage::Code_ code);

		InstChildMsg(Network::IMessage::Code_ code, void* objPtr, Network::IClient::Id_ clientId);

		// IMessage section
		virtual Network::IMessage::Size_ GetDataSize();

		// MessageImpl section
		virtual mc::result WriteBody(std::ostream& stream);

		virtual mc::result ReadBody(std::istream& stream);

	};

}

#endif // !INSTCHILDMSG_H__REMOTING__CORELIB__INCLUDED_
