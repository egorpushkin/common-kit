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
	interface IAccessProvider;
	/** . */ 
	typedef Strong< IAccessProvider > IAccessProviderPtr;

	/**
	 *
	 */
	interface IAccessPoint : public ICommon
	{

		virtual IAccessProviderPtr GetAccessProvider() = 0;

		virtual Iid GetIid() = 0;

		virtual result Advise(ICommonRef sink, unsigned long& cookie) = 0;

		virtual result Unadvise(unsigned long cookie) = 0;

		virtual ICommonPtr Find(unsigned long cookie) = 0;

		virtual ICommonPtr CreateSpreader() = 0;

		virtual result Spread(const Call& call) = 0;
	};

	// Smart pointers
	typedef Strong< IAccessPoint > IAccessPointPtr;
	typedef const IAccessPointPtr& IAccessPointRef;

	typedef Weak< IAccessPoint > IAccessPointWeak;
	typedef const IAccessPointWeak& IAccessPointWeakRef;

	// Containers
	// typedef std::pair< Guid, IAccessPointPtr > AccessPointPair;

	// typedef Container::IContainer< AccessPointPair > IAccessPoints;
	// typedef Container::IEnumerator< AccessPointPair > IAccessPointsEnum;
	
	// Containers' pointers
	// typedef ComPtr< IAccessPoints > IAccessPointsPtr;
	// typedef const IAccessPointsPtr& IAccessPointsRef;
	
	// typedef ComPtr< IAccessPointsEnum > IAccessPointsEnumPtr;
	// typedef const IAccessPointsEnumPtr& IAccessPointsEnumRef;

}

#endif // !IACCESSPOINT_H__MINCOM__INCLUDED_
