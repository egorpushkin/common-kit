#ifndef COMMANDEVENTSSTUB_H__MINCOM__INCLUDED_
#define COMMANDEVENTSSTUB_H__MINCOM__INCLUDED_

namespace MinCOM
{

	class CommandEventsStub
		: public CommonImpl< ICommandEvents >
	{
	public:

		CommandEventsStub();

		// ICommandEvents section
		virtual result ModifiedChanged(bool modified);

		// ICommon section
		virtual result Invoke(const CallData& call);		

	};

}

#endif // !COMMANDEVENTSSTUB_H__MINCOM__INCLUDED_
