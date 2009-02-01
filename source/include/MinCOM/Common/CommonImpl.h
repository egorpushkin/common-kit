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
				, targetS_()
				, targetW_()
			{
			}

		protected:

			/** . */
			long numRef_;

			/** . */
			Weak< ICommon > self_;

			/** . */
			Weak< ICommon > targetS_;

			/** . */
			Weak< ICommon > targetW_;

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

		virtual ~CommonImpl() {}

	public:

		CommonImpl()
			: CommonInternals()
		{
		}

		// ICommon section
		//////////////////////////////////////////////////////////////////////////

		/**
		 * Default implementation return NULL.
		 */
		virtual Strong< ICommon > Query(RefGuid /* targetIid */)
		{
			return NULL;
		}

		virtual void SetSelf(const Strong< ICommon > & self)
		{
			CommonInternals::self_ = self;
		}

		virtual Strong< ICommon > GetSelf()
		{
			return CommonInternals::self_;
		}

		virtual result PostInit()
		{
			return _S_OK;
		}

		virtual result SetTarget(const Strong< ICommon >& target, bool strong = true)
		{
			if ( strong )
				CommonInternals::targetS_ = target;
			else
				CommonInternals::targetW_ = target;
			return _S_OK;
		}

		virtual Strong< ICommon > GetTarget()
		{
			if ( CommonInternals::targetS_ )
				return CommonInternals::targetS_;
			else if ( CommonInternals::targetW_ )
				return CommonInternals::targetW_;
			return NULL;
		}

		virtual result Invoke(const CallData& callData)
		{
			ICommonPtr target(GetTarget());
			if ( target )
				return target->Invoke(callData);
			return _E_NOTINIT;
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
