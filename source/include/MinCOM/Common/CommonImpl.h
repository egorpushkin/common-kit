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

		class CommonInternals
		{

			CommonInternals(const CommonInternals&);
			CommonInternals& operator =(const CommonInternals&);

		protected:

			CommonInternals()
				: numRef_(0)
				, self_()
			{
			}

		protected:

			/** . */
			long numRef_;

			/** . */
			Weak< ICommon > self_;

		};

	} // namespace Private

	template
	<
		class T
	>
	class CommonImpl
		: virtual public Private::CommonInternals
		, public T
	{

		CommonImpl(const CommonImpl&);
		CommonImpl& operator =(const CommonImpl&);

	protected:

		CommonImpl()
			: CommonInternals()
		{
		}

		virtual ~CommonImpl() {}

	public:

		// ICommon section
		//////////////////////////////////////////////////////////////////////////

		/**
		 * Default implementation return NULL.
		 */
		virtual Strong< ICommon > Query(RefGuid /* targetIid */)
		{
			return NULL;
		}

		/**
		 * 
		 */
		virtual void SetSelf(const Strong< ICommon > & self)
		{
			CommonInternals::self_ = self;
		}

		/**
		 * 
		 */
		virtual Strong< ICommon > GetSelf()
		{
			return CommonInternals::self_;
		}

		// IReferenceCounter section
		virtual long IncrementReference()
		{
			return CoreCounter::Increment(CommonInternals::numRef_);                        
		}

		virtual long DecrementReference()
		{
			CoreCounter::Decrement(CommonInternals::numRef_);

			if ( CoreCounter::TestZero(CommonInternals::numRef_) )
			{
				delete this;
				return 0;
			}

			return CommonInternals::numRef_;
		}
	};

}

#endif // !COMMONIMPL_H__MINCOM__INCLUDED_
