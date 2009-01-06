#ifndef INVOKERESPMSG_H__REMOTING__CORELIB__INCLUDED_
#define INVOKERESPMSG_H__REMOTING__CORELIB__INCLUDED_

namespace Remoting
{

	class InvokeRespMsg
		: public Network::MessageImpl
	{
	public:

		InvokeRespMsg();

		InvokeRespMsg(mc::result response, const mc::Variant& retVal);

		// IMessage section
		virtual Network::IMessage::Size_ GetDataSize();

		// MessageImpl section
		virtual mc::result WriteBody(std::ostream& stream);

		virtual mc::result ReadBody(std::istream& stream);

	};

}

#endif // !INVOKERESPMSG_H__REMOTING__CORELIB__INCLUDED_
