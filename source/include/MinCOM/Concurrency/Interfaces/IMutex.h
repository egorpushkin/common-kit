/*
 * File name   : IMutex.h
 *
 * Copyright (c) 2009 Scientific Software
 *
 * Modification History:
 * Date        Name                Description
 * 2009-01-31  Egor Pushkin        Initial version
 */

#ifndef IMUTEX_H__MINCOM__INCLUDED_
#define IMUTEX_H__MINCOM__INCLUDED_

namespace MinCOM
{

	interface IMutex : public ISynchro
	{

		virtual result Create(bool obtain = false) = 0;

		virtual result Create(std::string name, bool obtain = false) = 0;

		virtual result Open(std::string name) = 0;

		virtual result Close() = 0;

		virtual result Release() = 0;
	};

	typedef Strong< IMutex > IMutexPtr;
	typedef const IMutexPtr& IMutexRef;

}

#endif // !IMUTEX_H__MINCOM__INCLUDED_
