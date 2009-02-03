/*
 * File name   : IList.h
 *
 * Copyright (c) 2009 Scientific Software
 *
 * Modification History:
 * Date        Name                Description
 * 2009-02-02  Egor Pushkin        Initial version
 */

#ifndef ILIST_H__MINCOM__INCLUDED_
#define ILIST_H__MINCOM__INCLUDED_

namespace MinCOM
{

	/**
	 * Basic interface for walking through any container.
	 */ 
	interface IList : public ICommon
	{
		
		


	};

	/**	. */
	typedef Strong< IList > IListPtr;
	/**	. */
	typedef const IListPtr& IListRef;

}

#endif // !ILIST_H__MINCOM__INCLUDED_
