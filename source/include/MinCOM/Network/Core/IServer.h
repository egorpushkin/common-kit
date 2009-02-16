/*
 * File name   : IServer.h
 *
 * Copyright (c) 2009 Scientific Software
 *
 * Modification History:
 * Date        Name                Description
 * 2009-02-04  Egor Pushkin        Initial version
 */

#ifndef ISERVER_H__MINCOM__INCLUDED_
#define ISERVER_H__MINCOM__INCLUDED_

namespace MinCOM
{

	interface IServer : public ICommon
	{
		
		virtual result AsyncAccept(const std::string& service) = 0;

		virtual void Run() = 0;

		virtual void Stop() = 0;

	};

	typedef Strong< IServer > IServerPtr;
	typedef const IServerPtr& IServerRef;

}

#endif // !ISERVER_H__MINCOM__INCLUDED_
