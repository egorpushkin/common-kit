/*
 * File name   : Events.h
 *
 * Copyright (c) 2009 Scientific Software
 *
 * Modification History:
 * Date        Name                Description
 * 2009-02-02  Egor Pushkin        Initial version
 */

#ifndef EVENTS_H__MINCOM__INCLUDED_
#define EVENTS_H__MINCOM__INCLUDED_

namespace MinCOM
{

	class Events
	{
	public:

		static result Advise(ICommonRef connectee, ICommonRef connector, unsigned long& cookie, RefIid apIid);

		static result Unadvise(ICommonRef connectee, unsigned long cookie, RefIid apIid);

	};

}

#endif // !IACCESSPOINT_H__MINCOM__INCLUDED_
