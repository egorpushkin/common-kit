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

		virtual result Release() = 0;
	};

	typedef Strong< IMutex > IMutexPtr;
	typedef const IMutexPtr& IMutexRef;

}

#endif // !IMUTEX_H__MINCOM__INCLUDED_
