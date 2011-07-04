/*
 * File name   : ICommands.h
 *
 * Copyright (c) 2009 Scientific Software
 *
 * Modification History:
 * Date        Name                Description
 * 2009-02-01  Egor Pushkin        Initial version
 */

#ifndef ICOMMANDS_H__MINCOM__INCLUDED_
#define ICOMMANDS_H__MINCOM__INCLUDED_

namespace MinCOM
{

	struct ICommands : public ICommon
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

	typedef Strong< ICommands > ICommandsPtr;
	typedef const ICommandsPtr& ICommandsRef;

	/* // Command events
	typedef enum tagCommandsEvents
	{

		AGENTID_REGISTERCOMMAND = 0xff010B01,

		AGENTID_MODIFIEDCHANGED

	} CommandEvents; */

}

#endif // !ICOMMANDS_H__MINCOM__INCLUDED_
