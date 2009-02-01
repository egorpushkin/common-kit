#ifndef EVENTSSPREADER_H__MINCOM__INCLUDED_
#define EVENTSSPREADER_H__MINCOM__INCLUDED_

namespace MinCOM
{

	class EventsSpreader
		: public CommonImpl< ICommon >
	{
	public:

		EventsSpreader(IAccessProviderRef accessProvider);

		// ICommon section
		virtual result Invoke(const CallData& call);

	private:

		IAccessProviderWeak accessProvider_;

	};

}

#endif // !EVENTSSPREADER_H__MINCOM__INCLUDED_
