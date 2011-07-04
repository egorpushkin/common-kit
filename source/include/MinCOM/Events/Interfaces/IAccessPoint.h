/*
 * File name   : IAccessPoint.h
 *
 * Copyright (c) 2009 Scientific Software
 *
 * Modification History:
 * Date        Name                Description
 * 2009-01-30  Egor Pushkin        Initial version
 */

#ifndef IACCESSPOINT_H__MINCOM__INCLUDED_
#define IACCESSPOINT_H__MINCOM__INCLUDED_

namespace MinCOM
{

	/** . */ 
	struct IAccessProvider;
	/** . */ 
	typedef Strong< IAccessProvider > IAccessProviderPtr;

	/**
	 *
	 */
	struct IAccessPoint : public ICommon
	{

		virtual IAccessProviderPtr GetAccessProvider() = 0;

		virtual Iid GetIid() = 0;

		/** 
		 * Registers new sink and provides caller with point-specific cookie.
		 *
		 * Does not allow to register sinks while spreading any event.
		 */ 
		virtual result Advise(ICommonRef sink, unsigned long& cookie) = 0;

		/** 
		 * Unregisters new sink.
		 *
		 * Allows to unregister sinks while spreading any event. Actual removal 
		 * occurs immediately after the pass is complete.
		 */
		virtual result Unadvise(unsigned long cookie) = 0;

		/** 
		 * Unregisters new sink.
		 *
		 * This is helper tool provided for convenience. Until access point
		 * supports cookies it is significantly faster to use cookie value
		 * to unregister sink.
		 *
		 * Allows to unregister sinks while spreading any event. Actual removal 
		 * occurs immediately after the pass is complete.
		 */
		virtual result Unadvise(ICommonRef sink) = 0;
	
		virtual ICommonPtr Find(unsigned long cookie) = 0;

		virtual ICommonPtr CreateSpreader() = 0;

		virtual result Spread(const Call& call) = 0;
	};

	// Smart pointers
	typedef Strong< IAccessPoint > IAccessPointPtr;
	typedef const IAccessPointPtr& IAccessPointRef;

	typedef Weak< IAccessPoint > IAccessPointWeak;
	typedef const IAccessPointWeak& IAccessPointWeakRef;

}

#endif // !IACCESSPOINT_H__MINCOM__INCLUDED_
