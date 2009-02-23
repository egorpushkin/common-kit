#ifndef DPROTOCOLSTUB_H__MINCOMLIB__INCLUDED_
#define DPROTOCOLSTUB_H__MINCOMLIB__INCLUDED_

namespace MinCOM
{

	class DProtocolStub
		: public CommonImpl< DProtocol >
	{
	public:

		DProtocolStub();

		// DProtocol section
		virtual result MessageArrived(IProtocolRef protocol, IMessageRef message);

		virtual result DataErrorOccured(IProtocolRef protocol);

		virtual result Disconnected(IProtocolRef protocol);

		// ICommon section
		virtual result Invoke(const Call& call);		

	};

}

#endif // !DPROTOCOLSTUB_H__MINCOMLIB__INCLUDED_
