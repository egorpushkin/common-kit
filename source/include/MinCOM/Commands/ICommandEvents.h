/*
 * File name   : ICommandEvents.h
 *
 * Copyright (c) 2009 Scientific Software
 *
 * Modification History:
 * Date        Name                Description
 * 2009-02-01  Egor Pushkin        Initial version
 */

#ifndef ICOMMANDEVENTS_H__MINCOM__INCLUDED_
#define ICOMMANDEVENTS_H__MINCOM__INCLUDED_

namespace MinCOM
{

	/**
	 * Designates an event sink interface that an application must implement 
	 * to receive event notifications from a container of command (ICommand).
	 * Each CLSID_Commands compatible object provides a way to subscribe on
	 * such events.
	 */
	interface ICommandEvents : public ICommon
	{	
		/**
		 * This event is fired when corresponding commands container
		 * changes it's modification state. Application should use this
		 * tool to propagate this information through it's object model.
		 */
		virtual result ModifiedChanged(bool modified) = 0;
	};

	typedef Strong< ICommandEvents > ICommandEventsPtr;
	typedef const ICommandEventsPtr& ICommandEventsRef;

}

#endif // !ICOMMANDEVENTS_H__MINCOM__INCLUDED_
