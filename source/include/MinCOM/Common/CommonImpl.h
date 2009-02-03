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

		/**
		 * Internal tool intended to store common object's data fields.
		 * CommonImpl inherit this tool virtually to prevent multiple 
		 * instantiation of data fields in multiple inheritance.
		 */
		class CommonInternals
		{

			CommonInternals(const CommonInternals&);
			CommonInternals& operator =(const CommonInternals&);

		protected:

			CommonInternals()
				: numRef_(0)
				, lock_()
				, self_()
				, parent_()
				, toolsS_()
				, toolsW_()
				, targetS_()
				, targetW_()
			{
			}

		protected:

			/** Holds internal reference counter. */
			long numRef_;

			/** Used to synchronize basic operations. */
			CoreMutex lock_;

			/** 
			 * Holds weak reference to the object. This field is initialized
			 * after object constructor is done but before call to PostInit.
			 */
			Weak< ICommon > self_;

			/** Holds weak reference to parent. */
			Weak< ICommon > parent_;

			/** Container to store child objects by strong link. */
			ToolsMap< ICommonPtr > toolsS_;

			/** Container to store child objects by weak link. */
			ToolsMap< ICommonWeak > toolsW_;

			/** Tool to redirect . */
			Strong< ICommon > targetS_;

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

		virtual result SetParent(const Strong< ICommon >& parent)
		{
			CoreMutexLock locker(CommonInternals::lock_);
			CommonInternals::parent_ = parent;
			return _S_OK;
		}

		virtual Strong< ICommon > GetParent()
		{
			CoreMutexLock locker(CommonInternals::lock_);
			return CommonInternals::parent_;
		}

		virtual result Attach(RefIid toolId, ICommonRef tool, bool strong = true) 
		{
			CoreMutexLock locker(CommonInternals::lock_);
			if ( strong )
			{
				CommonInternals::toolsS_.Attach(toolId, tool);
				CommonInternals::toolsW_.Remit(toolId);
			}
			else
			{
				CommonInternals::toolsW_.Attach(toolId, tool);
				CommonInternals::toolsS_.Remit(toolId);
			}
			return _S_OK;
		}

		virtual result Remit(RefIid toolId)
		{
			CommonInternals::toolsS_.Remit(toolId);
			CommonInternals::toolsW_.Remit(toolId);
			return _S_OK;
		}

		virtual ICommonPtr Acquire(RefIid toolId)
		{
			CoreMutexLock locker(CommonInternals::lock_);
			ICommonPtr tool = CommonInternals::toolsS_.Acquire(toolId);
			if ( tool )
				return tool;
			tool = CommonInternals::toolsW_.Acquire(toolId);
			if ( tool )
				return tool;
			return AcquireFromParent(toolId);
		}

		virtual result PostInit()
		{
			return _S_OK;
		}

		virtual result SetTarget(const Strong< ICommon >& target, bool strong = true)
		{
			CoreMutexLock locker(CommonInternals::lock_);
			if ( strong )
				CommonInternals::targetS_ = target;
			else
				CommonInternals::targetW_ = target;
			return _S_OK;
		}

		virtual Strong< ICommon > GetTarget()
		{
			CoreMutexLock locker(CommonInternals::lock_);
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

	protected:

		/** 
		 * Tries to acquire tool from parent object.
		 */
		ICommonPtr AcquireFromParent(RefIid toolId)
		{
			// Check whether parent is specified.
			ICommonPtr parent(GetParent());
			if ( !parent )
				return NULL;
			// Try to acquire required object from parent's collection.
			return parent->Acquire(toolId);
		}

		/**
		 * Provides access to internally hosted mutex. 
		 */
		CoreMutex& GetLock()
		{
			return CommonInternals::lock_;
		}

	};

}

#endif // !COMMONIMPL_H__MINCOM__INCLUDED_
