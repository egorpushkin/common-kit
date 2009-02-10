#ifndef DRAWDATASTUB_H__MINCOMLIB__INCLUDED_
#define DRAWDATASTUB_H__MINCOMLIB__INCLUDED_

namespace MinCOM
{

	class DRawDataStub
		: public CommonImpl< DRawData >
	{
	public:

		DRawDataStub();

		// DRawData section
		virtual result Connected(IConnectionRef connection);
		virtual result DataReceived(IConnectionRef connection);
		virtual result Disconnected(IConnectionRef connection);

		// ICommon section
		virtual result Invoke(const Call& call);		

	};

}

#endif // !DRAWDATASTUB_H__MINCOMLIB__INCLUDED_
