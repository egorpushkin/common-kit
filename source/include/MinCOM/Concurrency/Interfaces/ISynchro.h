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

	typedef enum tagWaitDelay
	{

		_INFINITE = 0xFFFFFFFF

	} tagWaitDelay;

	interface ISynchro : public ICommon
	{

		virtual result Wait(unsigned long milliseconds = _INFINITE) = 0;
	};

	typedef ComPtr< ISynchro > ISynchroPtr;
	typedef ComPtr< ISynchro, false > ISynchroWeak;

	typedef const ISynchroPtr& ISynchroRef;
	typedef const ISynchroWeak& ISynchroWeakRef;



}

#endif // !ISYNCHRO_H__MINCOM__INCLUDED_
