#ifndef ICOMMAND_H__MINCOM__COMMONKIT__INCLUDED_
#define ICOMMAND_H__MINCOM__COMMONKIT__INCLUDED_

namespace MinCOM
{

	interface ICommand : public ICommon
	{
		
		virtual result Configure(DispParamsRef params) = 0;

		virtual result Undo() = 0;

	};

	typedef ComPtr< ICommand > ICommandPtr;
	typedef const ICommandPtr& ICommandRef;

	// {f214fdf2-311b-41ea-b15e-c8f659ce3814} 
	MC_DEFINE_GUID(IID_ICommand, 
	0xf214fdf2, 0x311b, 0x41ea, 0xb1, 0x5e, 0xc8, 0xf6, 0x59, 0xce, 0x38, 0x14);

	template
	<
		class T
	>
	ICommandPtr InstantiateCommand(DispParamsRef params = NULL)
	{
		ICommandPtr command(ObjectCreator< T >(), IID_ICommand);

		if ( command && params )
			command->Configure(params);

		return command;
	}	

}

#endif // !ICOMMANDS_H__MINCOM__COMMONKIT__INCLUDED_
