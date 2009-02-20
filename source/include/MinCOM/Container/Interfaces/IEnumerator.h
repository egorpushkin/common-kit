/*
 * File name   : IEnumerator.h
 *
 * Copyright (c) 2009 Scientific Software
 *
 * Modification History:
 * Date        Name                Description
 * 2009-02-19  Egor Pushkin        Initial version
 */

#ifndef IENUMERATOR_H__MINCOM__INCLUDED_
#define IENUMERATOR_H__MINCOM__INCLUDED_

namespace MinCOM
{

	/**
	 * Basic interface for walking through any container.
	 */ 
	interface IEnumerator : public ICommon
	{

		virtual ICommonPtr GetCurrent() const = 0;

		virtual bool Next() = 0;  

		virtual bool Prev() = 0;  

		virtual bool HasNext() const = 0;

		virtual bool HasPrev() const = 0;

		virtual bool IsValid() const = 0;
	
	};

	/**	. */
	typedef Strong< IEnumerator > IEnumeratorPtr;
	/**	. */
	typedef const IEnumeratorPtr& IEnumeratorRef;
	/**	. */
	typedef Weak< IEnumerator > IIEnumeratorWeak;

}

#endif // !IENUMERATOR_H__MINCOM__INCLUDED_
