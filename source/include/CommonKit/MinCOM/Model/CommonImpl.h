/*
 * File name   : CommonImpl.h
 *
 * Copyright (c) 2008 Scientific Software
 *
 * Modification History:
 * Date        Name                Description
 * 2008-12-29  Egor Pushkin        Initial version
 */

#ifndef COMMONIMPL_H__MINCOM__INCLUDED_
#define COMMONIMPL_H__MINCOM__INCLUDED_

namespace MinCOM
{

	namespace Private
	{

		class ReferenceDecl
		{
			ReferenceDecl(const ReferenceDecl&);
			ReferenceDecl& operator =(const ReferenceDecl&);
		protected:

			ReferenceDecl()
				: numRef_(0)
			{
			}

		protected:
			long numRef_;
		};

	} // namespace Private

	template
	<
		class T
	>
	class CommonImpl
		: virtual public Private::ReferenceDecl
		, public T
	{
		CommonImpl(const CommonImpl&);
		CommonImpl& operator =(const CommonImpl&);
	protected:

		CommonImpl()
			: ReferenceDecl()
		{
		}

		virtual ~CommonImpl() {}

	public:

		// IReferenceCounter section
		virtual unsigned long IncrementReference()
		{
			return CoreCounter::Increment(ReferenceDecl::numRef_);                        
		}

		virtual unsigned long DecrementReference()
		{
			CoreCounter::Decrement(ReferenceDecl::numRef_);

			if ( CoreCounter::TestZero(ReferenceDecl::numRef_) )
			{
				delete this;
				return 0;
			}

			return ReferenceDecl::numRef_;
		}

	};

}

#endif // !COMMONIMPL_H__MINCOM__INCLUDED_
