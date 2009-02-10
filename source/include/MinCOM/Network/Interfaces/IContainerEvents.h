/*
 * File name   : IContainerEvents.h
 *
 * Copyright (c) 2009 Scientific Software
 *
 * Modification History:
 * Date        Name                Description
 * 2009-02-01  Egor Pushkin        Initial version
 */

#ifndef ICONTAINEREVENTS_H__MINCOM__INCLUDED_
#define ICONTAINEREVENTS_H__MINCOM__INCLUDED_

namespace MinCOM
{

	/**
	 * Notifies subscribers on container events.
	 */
	interface IContainerEvents : public ICommon
	{	
		/** 
		 * 
		 */
		virtual result ElementAdded(ICommonRef container, ICommonRef element) = 0;

		/**
		 * 
		 */
		virtual result ElementRemoved(ICommonRef container, ICommonRef element) = 0;

		/**
		 * 
		 */
		virtual result ContainerModified(ICommonRef container) = 0;

		/**
		 * 
		 */
		virtual result ContainerCleared(ICommonRef container) = 0;
	};

	typedef Strong< IContainerEvents > IContainerEventsPtr;
	typedef const IContainerEventsPtr& IContainerEventsRef;

}

#endif // !ICONTAINEREVENTS_H__MINCOM__INCLUDED_
