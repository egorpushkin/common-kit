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
		virtual result MessageArrived(IMessageRef message);

		// ICommon section
		virtual result Invoke(const Call& call);		

	};

}

#endif // !DPROTOCOLSTUB_H__MINCOMLIB__INCLUDED_
