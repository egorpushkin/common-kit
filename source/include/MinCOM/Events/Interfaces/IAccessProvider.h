/*
 * File name   : IAccessProvider.h
 *
 * Copyright (c) 2009 Scientific Software
 *
 * Modification History:
 * Date        Name                Description
 * 2009-01-30  Egor Pushkin        Initial version
 */

#ifndef IACCESSPROVIDER_H__MINCOM__INCLUDED_
#define IACCESSPROVIDER_H__MINCOM__INCLUDED_

namespace MinCOM
{

	/** 
	 * 
	 */
	interface IAccessProvider : public ICommon
	{

		virtual result Advise(RefIid iid, IAccessPointRef accessPoint) = 0;

		virtual result Unadvise(RefIid iid) = 0;

		virtual IAccessPointPtr Find(RefIid iid) = 0;

		virtual result Spread(const CallData& call) = 0;
	};

	typedef Strong< IAccessProvider > IAccessProviderPtr;
	typedef const IAccessProviderPtr& IAccessProviderRef;

	typedef Weak< IAccessProvider > IAccessProviderWeak;
	typedef const IAccessProviderWeak& IAccessProviderWeakRef;

}

#endif // !IACCESSPROVIDER_H__MINCOM__INCLUDED_
