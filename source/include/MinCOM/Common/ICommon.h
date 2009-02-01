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
	 * 
	 */
	interface ICommon : public IReferenceCounter
	{
	public:

		/**
		 * Method to cast pointer to any object's control interface to
		 * pointer to another interface which is potentially supported by 
		 * the object.
		 */
		template
		<
			class T1
		>
		T1 * Cast()
		{
			return dynamic_cast< T1* >(this);
		}

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
		virtual result Invoke(const CallData& call) = 0;

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
