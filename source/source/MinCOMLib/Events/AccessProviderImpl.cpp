#include "Common/Common.h"

#include "AccessPointImpl.h"

namespace MinCOM
{

	// TODO: Implement delayed registering and unregistering of stubs.

	AccessProviderImpl::AccessProviderImpl()
		: CommonImpl< IAccessProvider >()
		, accessPoints_()
	{
		// Advise default access point.
		Advise( TypeInfo< ICommon >::GetGuid() );
	}

	// IAccessProvider section
	result AccessProviderImpl::Advise(RefIid iid, IAccessPointRef accessPoint)
	{
		CoreMutexLock locker(CommonImpl< IAccessProvider >::GetLock());

		// Check input arguments for correctness.
		if ( !accessPoint )
			return _E_INVALIDARG;
		// Check whether access point with specified id already advised.
		AccessPoints_::iterator iter = accessPoints_.find(iid);
		if ( accessPoints_.end() != iter )
			return _E_FAIL;
		// Register access point after all checks are passed.
		accessPoints_.insert(AccessPoints_::value_type(iid, accessPoint));
		return _S_OK;
	}

	result AccessProviderImpl::Unadvise(RefIid iid)
	{
		CoreMutexLock locker(CommonImpl< IAccessProvider >::GetLock());

		// Check whether sink with specified cookie exists.
		AccessPoints_::iterator iter = accessPoints_.find(iid);
		if ( iter == accessPoints_.end() )
			return _E_FAIL;
		// Remove access point from map.
		accessPoints_.erase(iter);
		return _S_OK;
	}

	IAccessPointPtr AccessProviderImpl::Find(RefIid iid)
	{
		CoreMutexLock locker(CommonImpl< IAccessProvider >::GetLock());

		// Check whether sink with specified cookie exists.
		AccessPoints_::iterator iter = accessPoints_.find(iid);
		if ( iter == accessPoints_.end() )
			return NULL;
		// Access point is found. Provide caller with it.
		return (*iter).second;
	}

	result AccessProviderImpl::Spread(const Call& call)
	{
		CoreMutexLock locker(CommonImpl< IAccessProvider >::GetLock());

		// Prevent destruction of this object during spreading event.
		IAccessProviderPtr strongThis( CommonImpl< IAccessProvider >::GetSelf() );

		// Walk through the entire list of access points and spread the event.
		for ( AccessPoints_::iterator iter = accessPoints_.begin() ; accessPoints_.end() != iter ; ++iter )
		{
			(*iter).second->Spread(call);
		}

		return _S_OK;
	}

	// Protected tools
	//////////////////////////////////////////////////////////////////////////

	ICommonPtr AccessProviderImpl::Advise(RefIid eventsIid)
	{
		// Construct access point.
		IAccessPointPtr accessPoint( Class< AccessPointImpl >::Create( 
			CommonImpl< IAccessProvider >::GetSelf(), eventsIid ) );
		if ( !accessPoint )
			return NULL;
		// Produce corresponding events spreader.
		ICommonPtr eventsSpreader = Object::CreateStub( 
			eventsIid, accessPoint->CreateSpreader(), true );
		if ( !eventsSpreader )
			return NULL;		
		// Register access point.
		if ( Error::IsFailed(Advise(eventsIid, accessPoint)) )
			return NULL;
		return eventsSpreader;
	}

	ICommonPtr AccessProviderImpl::AdviseAndThrow(RefIid eventsIid)
	{
		ICommonPtr eventsSpreader = this->Advise(eventsIid);
		if ( !eventsSpreader )
		{
			// TODO: Add mo details to generated exception here.
			throw std::exception();
		}
		return eventsSpreader;
	}

	ICommonPtr AccessProviderImpl::Advise(IAccessProviderRef accessProvider, RefIid eventsIid)
	{
		// Construct access point.
		IAccessPointPtr accessPoint( Class< AccessPointImpl >::Create( 
			accessProvider, eventsIid ) );
		if ( !accessPoint )
			return NULL;
		// Produce corresponding events spreader.
		ICommonPtr eventsSpreader = Object::CreateStub( 
			eventsIid, accessPoint->CreateSpreader(), true );
		if ( !eventsSpreader )
			return NULL;		
		// Register access point.
		if ( Error::IsFailed(accessProvider->Advise(eventsIid, accessPoint)) )
			return NULL;
		return eventsSpreader;
	}

	ICommonPtr AccessProviderImpl::AdviseAndThrow(IAccessProviderRef accessProvider, RefIid eventsIid)
	{
		ICommonPtr eventsSpreader = AccessProviderImpl::Advise(accessProvider, eventsIid);
		if ( !eventsSpreader )
		{
			// TODO: Add mo details to generated exception here.
			throw std::exception();
		}
		return eventsSpreader;
	}

}
