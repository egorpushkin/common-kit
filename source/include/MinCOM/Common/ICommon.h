/*
 * File name   : ICommon.h
 *
 * Copyright (c) 2008 Scientific Software
 *
 * Modification History:
 * Date        Name                Description
 * 2008-12-14  Egor Pushkin        Initial version
 */

#ifndef ICOMMON_H__MINCOM__INCLUDED_
#define ICOMMON_H__MINCOM__INCLUDED_

namespace MinCOM
{

	/**
	 * Class hierarchy root. 
	 */
	struct ICommon : public IReferenceCounter
	{
	public:

		/**
		 * Tool to power interchangeable (object specific) casting mechanism.
		 * This tool should check whether current object support target 
		 * interface with specified iid or figure out what to do otherwise.
		 *
		 * Default implementation of this tool (provided by MinCOM) should 
		 * return NULL to avoid superfluous checks when processing local
		 * monolithic objects.
		 */
		virtual Strong< ICommon > Query(RefGuid targetIid) = 0;

		/**
		 * 
		 */
		virtual void SetSelf(const Strong< ICommon > & self) = 0;

		/**
		 * 
		 */
		virtual Strong< ICommon > GetSelf() = 0;

		/**
		 * Returns unique object identifier. This value is unique in bounds 
		 * of caller process. Moreover, this value has sense only in bounds
		 * of caller and has no relationship to object host process (if these
		 * processes do not coinside).
		 */
		virtual size_t GetCookie() = 0;

		/** 
		 * Tests whether specified cookie corresponds to this object.
		 */
		virtual bool TestCookie(size_t cookie) = 0;

		/**
		 *
		 */
		virtual result SetParent(const Strong< ICommon >& parent) = 0;

		/**
		 *
		 */
		virtual Strong< ICommon > GetParent() = 0;

		/**
		 *
		 */
		virtual result Attach(RefIid toolId, const Strong< ICommon >& tool, bool strong = true) = 0;

		/**
		 *
		 */
		virtual result Remit(RefIid toolId) = 0;

		/**
		 *
		 */
		virtual Strong< ICommon > Acquire(RefIid toolId) = 0;

		/**
		 * Tool to perform required initializations.
		 * Several actions cannot be performed in constructor.
		 */
		virtual result PostInit() = 0;

		/**
		 * Allows user to speficy helper object so current one has a chance to 
		 * delegate certain set of its operations. Provides basic support for 
		 * proxy/stub mechanism.
		 */
		virtual result SetTarget(const Strong< ICommon >& target, bool strong = true) = 0;

		/**
		 * Provides caller with the target which is currently attached.
		 */
		virtual Strong< ICommon > GetTarget() = 0;

		/**
		 * Allows user to make a call in raw manner. Provides basic support for 
		 * events dispatching and remoting.
		 */
		virtual result Invoke(const Call& call) = 0;

	protected:

		virtual ~ICommon()
		{
		}
		
	};

	/**	. */
	typedef Strong< ICommon > ICommonPtr;
	/**	. */
	typedef const ICommonPtr& ICommonRef;
	/**	. */
	typedef Weak< ICommon > ICommonWeak;

}

#endif // !ICOMMON_H__MINCOM__INCLUDED_
