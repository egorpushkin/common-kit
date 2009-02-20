/*
 * File name   : DContainer.h
 *
 * Copyright (c) 2009 Scientific Software
 *
 * Modification History:
 * Date        Name                Description
 * 2009-02-01  Egor Pushkin        Initial version
 */

#ifndef DCONTAINER_H__MINCOM__INCLUDED_
#define DCONTAINER_H__MINCOM__INCLUDED_

namespace MinCOM
{

	/**
	 * Notifies subscribers on container events.
	 */
	interface DContainer : public ICommon
	{	
		/**
		 * 
		 */
		virtual result ContainerModified(ICommonRef container) = 0;
	};

	typedef Strong< DContainer > DContainerPtr;
	typedef const DContainerPtr& DContainerRef;

}

#endif // !DCONTAINER_H__MINCOM__INCLUDED_
