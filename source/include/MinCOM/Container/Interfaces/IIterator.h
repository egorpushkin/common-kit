/*
 * File name   : IIterator.h
 *
 * Copyright (c) 2009 Scientific Software
 *
 * Modification History:
 * Date        Name                Description
 * 2009-02-02  Egor Pushkin        Initial version
 */

#ifndef IITERATOR_H__MINCOM__INCLUDED_
#define IITERATOR_H__MINCOM__INCLUDED_

namespace MinCOM
{

	/**
	 * Basic interface for walking through any container.
	 */ 
	interface IIterator : public ICommon
	{

		virtual ICommonPtr operator*() const = 0;

		virtual Strong< IIterator > operator++( ) = 0;  

		virtual Strong< IIterator > operator++( int ) = 0;





	};

	/**	. */
	typedef Strong< IIterator > IIteratorPtr;
	/**	. */
	typedef const IIteratorPtr& IIteratorRef;
	/**	. */
	typedef Weak< IIterator > IIteratorWeak;

}

#endif // !IITERATOR_H__MINCOM__INCLUDED_
