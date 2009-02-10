#ifndef DCOMMANDSSTUB_H__MINCOMLIB__INCLUDED_
#define DCOMMANDSSTUB_H__MINCOMLIB__INCLUDED_

namespace MinCOM
{

	class DCommandsStub
		: public CommonImpl< DCommands >
	{
	public:

		DCommandsStub();

		// ICommandEvents section
		virtual result ModifiedChanged(bool modified);

		// ICommon section
		virtual result Invoke(const Call& call);		

	};

}

#endif // !DCOMMANDSSTUB_H__MINCOMLIB__INCLUDED_
