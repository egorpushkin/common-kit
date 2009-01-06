#ifndef INSTANTIATIONMESSAGE_H__REMOTING__CORELIB__INCLUDED_
#define INSTANTIATIONMESSAGE_H__REMOTING__CORELIB__INCLUDED_

namespace Remoting
{

	class InstMsg
		: public Network::MessageImpl
	{
	public:

		InstMsg();

		InstMsg(mc::RefClsid clsid);

		// IMessage section
		virtual Network::IMessage::Size_ GetDataSize();

		// MessageImpl section
		virtual mc::result WriteBody(std::ostream& stream);

		virtual mc::result ReadBody(std::istream& stream);

	};

}

#endif // !INSTANTIATIONMESSAGE_H__REMOTING__CORELIB__INCLUDED_
