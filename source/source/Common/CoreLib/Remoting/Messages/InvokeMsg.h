#ifndef INVOKEMSG_H__REMOTING__CORELIB__INCLUDED_
#define INVOKEMSG_H__REMOTING__CORELIB__INCLUDED_

namespace Remoting
{

	class InvokeMsg
		: public mc::CommonImpl< IInvokeMsg >
		, public Network::MessageImpl
	{
	public:

		InvokeMsg();

		InvokeMsg(mc::DispId idMember, mc::DispParamsRef dispParams, mc::RefIid iid);

		// ICommon section
		DECLARE_INTERFACE_MAP()		

		// IInvokeMessage section
		virtual void SetParams(mc::DispParamsRef dispParams);

		virtual mc::DispParamsPtr GetParams();

		// IMessage section
		virtual Network::IMessage::Size_ GetDataSize();

		// MessageImpl section
		virtual mc::result WriteBody(std::ostream& stream);

		virtual mc::result ReadBody(std::istream& stream);

	private:

		// Private tools
		Network::IMessage::Size_ GetParamsSize();

	private:

		mc::DispParamsPtr dispParams_;

	};

}

#endif // !INVOKEMSG_H__REMOTING__CORELIB__INCLUDED_
