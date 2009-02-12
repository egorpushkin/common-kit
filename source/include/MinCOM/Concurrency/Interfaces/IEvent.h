/*
 * File name   : IEvent.h
 *
 * Copyright (c) 2009 Scientific Software
 *
 * Modification History:
 * Date        Name                Description
 * 2009-01-31  Egor Pushkin        Initial version
 */

#ifndef IEVENT_H__MINCOM__INCLUDED_
#define IEVENT_H__MINCOM__INCLUDED_

namespace MinCOM
{

	interface IEvent : public ISynchro
	{

		virtual result Pulse() = 0;

		virtual result Set() = 0;

		virtual result Reset() = 0;
	};

	typedef Strong< IEvent > IEventPtr;
	typedef const IEventPtr& IEventRef;

	IEventPtr InstantiateEvent();

}

#endif // !IEVENT_H__MINCOM__INCLUDED_
