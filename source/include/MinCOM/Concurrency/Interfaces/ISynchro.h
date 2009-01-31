/*
 * File name   : ISynchro.h
 *
 * Copyright (c) 2009 Scientific Software
 *
 * Modification History:
 * Date        Name                Description
 * 2009-01-31  Egor Pushkin        Initial version
 */

#ifndef ISYNCHRO_H__MINCOM__INCLUDED_
#define ISYNCHRO_H__MINCOM__INCLUDED_

namespace MinCOM
{

	interface ISynchro : public ICommon
	{

		typedef enum tagConsts
		{

			_INFINITE = 0xFFFFFFFF

		} Consts;

		virtual result Wait(unsigned long delay = _INFINITE) = 0;
	};

	typedef Strong< ISynchro > ISynchroPtr;
	typedef const ISynchroPtr& ISynchroRef;

}

#endif // !ISYNCHRO_H__MINCOM__INCLUDED_
