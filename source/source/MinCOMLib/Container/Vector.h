#ifndef VECTOR_H__MINCOM__INCLUDED_
#define VECTOR_H__MINCOM__INCLUDED_

#include "IPrivateIterator.h"
#include "Iterator.h"

namespace MinCOM
{

	class Vector
		: public CommonImpl< IVector >
		, public APImpl
	{
	public:

		typedef IPrivateIterator< std::vector< ICommonPtr >, Vector > IPrivateIterator_;
		typedef Strong< IPrivateIterator_ > IPrivateIteratorPtr_;
		typedef Iterator< std::vector< ICommonPtr >, Vector > Iterator_;

	public:

		Vector();
		Vector(size_t count);

		// IVector section
		virtual void Assign(size_t count, ICommonRef value);

		virtual void Assign(IIteratorRef first, IIteratorRef last);

		virtual IIteratorPtr Begin();

		virtual IIteratorPtr End();

		virtual void PushBack(ICommonRef val);


		virtual void Clear();

		// ICommon section
		virtual result PostInit();		

	private:

		std::vector< ICommonPtr > stdVector_;

		/** . */
		DContainerPtr eventsSpreader_;

	};

}

#endif // !VECTOR_H__MINCOM__INCLUDED_
