#ifndef COMMANDIMPL_H__MINCOM__COMMONKIT__INCLUDED_
#define COMMANDIMPL_H__MINCOM__COMMONKIT__INCLUDED_

namespace MinCOM
{

	class CommandImpl 
		: public CommonImpl< ICommand >
	{
	public:

		CommandImpl();

		// ICommon section
		DECLARE_INTERFACE_MAP()

		// ICommand section
		virtual result Configure(DispParamsRef params);

		virtual result Undo();

	protected:

		DispParamsPtr params_;

	};

}

#endif // !COMMANDIMPL_H__MINCOM__COMMONKIT__INCLUDED_
