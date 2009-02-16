#ifndef DSERVERSTUB_H__MINCOMLIB__INCLUDED_
#define DSERVERSTUB_H__MINCOMLIB__INCLUDED_

namespace MinCOM
{

	class DServerStub
		: public CommonImpl< DServer >
	{
	public:

		DServerStub();

		// DServer section
		virtual result ConnectionAccepted(IConnectionRef connection);

		// ICommon section
		virtual result Invoke(const Call& call);		

	};

}

#endif // !DSERVERSTUB_H__MINCOMLIB__INCLUDED_
