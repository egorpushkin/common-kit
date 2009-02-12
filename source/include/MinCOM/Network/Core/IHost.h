/*
 * File name   : IHost.h
 *
 * Copyright (c) 2009 Scientific Software
 *
 * Modification History:
 * Date        Name                Description
 * 2009-02-04  Egor Pushkin        Initial version
 */

#ifndef IHOST_H__MINCOM__INCLUDED_
#define IHOST_H__MINCOM__INCLUDED_

namespace MinCOM
{

	interface IHost : public ICommon
	{

		virtual std::string GetHost() = 0;

		virtual std::string GetService() = 0;

	};

	typedef Strong< IHost > IHostPtr;
	typedef const IHostPtr& IHostRef;

}

#endif // !IHOST_H__MINCOM__INCLUDED_
