/*
 * File name   : ICommand.h
 *
 * Copyright (c) 2009 Scientific Software
 *
 * Modification History:
 * Date        Name                Description
 * 2009-02-01  Egor Pushkin        Initial version
 */

#ifndef ICOMMAND_H__MINCOM__INCLUDED_
#define ICOMMAND_H__MINCOM__INCLUDED_

namespace MinCOM
{

	struct ICommand : public ICommon
	{

		virtual result Undo() = 0;
	};

	typedef Strong< ICommand > ICommandPtr;
	typedef const ICommandPtr& ICommandRef;

}

#endif // !ICOMMAND_H__MINCOM__INCLUDED_
