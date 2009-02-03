/*
 * File name   : IVector.h
 *
 * Copyright (c) 2009 Scientific Software
 *
 * Modification History:
 * Date        Name                Description
 * 2009-02-02  Egor Pushkin        Initial version
 */

#ifndef IVECTOR_H__MINCOM__INCLUDED_
#define IVECTOR_H__MINCOM__INCLUDED_

namespace MinCOM
{

	/**
	 * Basic interface for walking through any container.
	 */ 
	interface IVector : public ICommon
	{
		
		virtual void Assign(size_t count, ICommonRef value) = 0;

		virtual void Assign(IIteratorRef first, IIteratorRef last) = 0;

		virtual IIteratorPtr Begin() = 0;

		virtual IIteratorPtr End() = 0;
	
		virtual void PushBack(ICommonRef val) = 0;

		virtual void Clear() = 0;

	};

	/**	. */
	typedef Strong< IVector > IVectorPtr;
	/**	. */
	typedef const IVectorPtr& IVectorRef;

}

#endif // !IVECTOR_H__MINCOM__INCLUDED_
