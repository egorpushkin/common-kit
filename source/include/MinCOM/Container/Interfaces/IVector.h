/*
 * File name   : IVector.h
 *
 * Copyright (c) 2009 Scientific Software
 *
 * Modification History:
 * Date        Name                Description
 * 2009-02-19  Egor Pushkin        Initial version
 */

#ifndef IVECTOR_H__MINCOM__INCLUDED_
#define IVECTOR_H__MINCOM__INCLUDED_

namespace MinCOM
{

	/**
	 * Simple wrapper std::vector< ICommonPtr > over.
	 *
	 * The purpose of this interface is to provide dispatchable container. 
	 *  
	 * Next goal is separation of reader and writer interfaces. IEnumerator 
	 * provides access for enumerating the contents of container without a 
	 * chance to modify it.
	 *
	 * Thus, this interface is not compatible with std::vector and does not
	 * provide operations with element ranges. Current revision does no also 
	 * provide support for 'iterator' concept. 
	 *
	 * See Vector and VectorEnumerator classes for more details on thread 
	 * safety and performance issues.
	 *
	 * Caution: Be especially attentive to the validness of enumerator objects. 
	 * See IEnumerator documentation on details. By default assume that any 
	 * enumerator becomes invalid after container modification.
	 */ 
	interface IVector : public ICommon
	{
		// TODO: Const members.
			
		virtual ICommonPtr At(size_t pos) = 0;

		virtual ICommonPtr Back() = 0;

		virtual size_t Capacity() = 0;

		virtual void Clear() = 0;

		virtual bool Empty() = 0;

		virtual void Erase(ICommonRef val) = 0;

		virtual ICommonPtr Front() = 0;

		virtual void Insert(size_t pos, ICommonRef val) = 0;

		virtual size_t MaxSize() = 0;

		virtual void PopBack() = 0;
	
		virtual void PushBack(ICommonRef val) = 0;

		virtual void Resize(size_t newSize) = 0;

		virtual size_t Size() = 0;
		
		virtual void Swap(const Strong< IVector >& right) = 0;

		virtual IEnumeratorPtr GetEnumerator(size_t pos = 0) = 0;

	};

	/**	. */
	typedef Strong< IVector > IVectorPtr;
	/**	. */
	typedef const IVectorPtr& IVectorRef;
	/**	. */
	typedef Weak< IVector > IVectorWeak;

}

#endif // !IVECTOR_H__MINCOM__INCLUDED_
