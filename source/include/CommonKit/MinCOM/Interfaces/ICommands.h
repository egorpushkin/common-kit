#ifndef ICOMMANDS_H__MINCOM__COMMONKIT__INCLUDED_
#define ICOMMANDS_H__MINCOM__COMMONKIT__INCLUDED_

namespace MinCOM
{

	interface ICommands : public ICommon
	{
		
		virtual result Undo() = 0;

		virtual result Redo() = 0;

		virtual bool CanUndo() = 0;

		virtual bool CanRedo() = 0;

		virtual result Add(ICommandRef command) = 0;

		virtual void Enable(bool enable) = 0;

		virtual void SetModified(bool modified) = 0;

		virtual bool IsModified() = 0;

	};

	typedef ComPtr< ICommands > ICommandsPtr;
	typedef const ICommandsPtr& ICommandsRef;

	// {6c047399-208b-48ca-9b48-cabd6bf999af} 
	MC_DEFINE_GUID(IID_ICommands, 
	0x6c047399, 0x208b, 0x48ca, 0x9b, 0x48, 0xca, 0xbd, 0x6b, 0xf9, 0x99, 0xaf);

	// {ad9503d2-8c64-4961-a7a1-de144d5262dc} 
	MC_DEFINE_GUID(CLSID_Commands, 
	0xad9503d2, 0x8c64, 0x4961, 0xa7, 0xa1, 0xde, 0x14, 0x4d, 0x52, 0x62, 0xdc);

	ICommandsPtr InstantiateCommands();

	// Command events
	typedef enum tagCommandsEvents
	{

		AGENTID_REGISTERCOMMAND = 0xff010B01,

		AGENTID_MODIFIEDCHANGED

	} CommandEvents;

}

#endif // !ICOMMANDS_H__MINCOM__COMMONKIT__INCLUDED_
