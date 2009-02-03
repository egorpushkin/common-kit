#include "Common/Common.h"

namespace MinCOM
{

	AccessProviderImpl::AccessProviderImpl()
		: CommonImpl< IAccessProvider >()
		, lock_()
		, accessPoints_()
	{
		// Advise default access point.
		Advise( TypeInfo< ICommon >::GetGuid() );
	}

	// IAccessProvider section
	result AccessProviderImpl::Advise(RefIid iid, IAccessPointRef accessPoint)
	{
		CoreMutexLock locker(lock_);

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
		CoreMutexLock locker(lock_);

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
		CoreMutexLock locker(lock_);

		// Check whether sink with specified cookie exists.
		AccessPoints_::iterator iter = accessPoints_.find(iid);
		if ( iter == accessPoints_.end() )
			return NULL;
		// Access point is found. Provide caller with it.
		return (*iter).second;
	}

	result AccessProviderImpl::Spread(const CallData& call)
	{
		CoreMutexLock locker(lock_);

		// Walk through the entire list of access points and spread the event.
		for ( AccessPoints_::iterator iter = accessPoints_.begin() ; accessPoints_.end() != iter ; ++iter )
		{
			(*iter).second->Spread(call);
		}

		return _S_OK;
	}

	// Public events tools
	/* result AccessProviderImpl::SpreadEventCore(IAccessEntriesEnumRef entries, DispSpreader& spreader)
	{
		// Spread event
		ForEach(entries, spreader);

		// Return error code
		return spreader.GetLastError();
	} */

	// Protected tools
	IAccessPointPtr AccessProviderImpl::Advise(RefIid eventsIid)
	{
		// Construct access point.
		ICommonPtr accessPoint( Class< AccessPointImpl >::Create( 
			CommonImpl< IAccessProvider >::GetSelf(), 
			eventsIid ) );
		// Register aceess point.
		if ( Error::IsFailed(Advise(eventsIid, accessPoint)) )
			return NULL;
		return accessPoint;
	}

}
