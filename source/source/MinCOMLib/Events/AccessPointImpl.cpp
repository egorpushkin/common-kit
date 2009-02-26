#include "Common/Common.h"

#include "EventsSpreader.h"
#include "AccessPointImpl.h"

namespace MinCOM
{

	// TODO: Find stub at the stage of advising sink.
	// TODO: Implement delayed registering of sinks.

	AccessPointImpl::AccessPointImpl(IAccessProviderRef accessProvider, RefGuid iid)
		: CommonImpl< IAccessPoint >()
		, accessProvider_(accessProvider)
		, iid_(iid)
		, accessEntries_()
		, spreading_( false )
		, pendingRemoval_()
	{
	}

	// IAccessPoint section
	IAccessProviderPtr AccessPointImpl::GetAccessProvider()
	{
		return accessProvider_;
	}

	Iid AccessPointImpl::GetIid()
	{
		return iid_;
	}

	result AccessPointImpl::Advise(ICommonRef sink, unsigned long& cookie)
	{
		CoreMutexLock locker(CommonImpl< IAccessPoint >::GetLock());

		// Prevents registering new sinks while spreading an event.
		if ( spreading_ )
		{
			return _E_FAIL;
		}

		// Check input arguments for correctness.
		if ( !sink )
			return _E_INVALIDARG;
		// Check whether such sink already advised and prepare new cookie 
		//  at the same time.
		unsigned long allocatedCooie = 1;
		for ( AccessEntries_::iterator iter = accessEntries_.begin() ; accessEntries_.end() != iter ; ++iter  )
		{
			ICommonPtr entrySink((*iter).second);
			if ( entrySink == sink )
			{
				cookie = (*iter).first;
				return _S_OK;
			}
			if ( (*iter).first == allocatedCooie )
				++allocatedCooie;
		}
		// Insert new sink
		accessEntries_.insert(AccessEntries_::value_type(allocatedCooie, sink));
		cookie = allocatedCooie;
		return _S_OK;
	}

	result AccessPointImpl::Unadvise(unsigned long cookie)
	{		
		CoreMutexLock locker(CommonImpl< IAccessPoint >::GetLock());

		// Check whether spreading is in process.
		if ( spreading_ )
		{
			pendingRemoval_.insert(cookie);
			return _S_OK;
		}

		// Unadvise sink immediately.
		return UnadviseInternl( cookie );
	}

	result AccessPointImpl::Unadvise(ICommonRef sink)
	{
		CoreMutexLock locker(CommonImpl< IAccessPoint >::GetLock());
	
		// Find corresponding cookie. 
		unsigned long cookie = 0;
		for ( AccessEntries_::iterator iter = accessEntries_.begin() ; accessEntries_.end() != iter ; ++iter )
		{
			ICommonPtr strongSink((*iter).second);
			if ( strongSink == sink )
			{
				cookie = (*iter).first;
				break;
			}
		}

		if ( 0 == cookie )
			// Sink was not found.
			return _E_INVALIDARG;

		// Unregister sink with known cookie in regular way.
		return Unadvise( cookie );
	}

	ICommonPtr AccessPointImpl::Find(unsigned long cookie)
	{
		CoreMutexLock locker(CommonImpl< IAccessPoint >::GetLock());

		// Check whether sink with specified cookie exists.
		AccessEntries_::iterator iter = accessEntries_.find(cookie);
		if ( iter == accessEntries_.end() )
			return NULL;
		// Sink is found. Provide caller with found sink.
		return (*iter).second;
	}

	ICommonPtr AccessPointImpl::CreateSpreader()
	{
		return Class< EventsSpreader >::Create(GetAccessProvider());
	}

	result AccessPointImpl::Spread(const Call& call)
	{
		CoreMutexLock locker(CommonImpl< IAccessPoint >::GetLock());

		// Prevent recursive events spreading.
		if ( spreading_ )
			return _E_FAIL;

		spreading_ = true;

		// Create stub preliminary. We should not create stub earlier because 
		// it may not be yet registered by that time.
		ICommonPtr stub( Object::Create(iid_) );

		// Walk through the entire list of sinks and notify each of them on the 
		// event.
		for ( AccessEntries_::iterator iter = accessEntries_.begin() ; accessEntries_.end() != iter ; ++iter )
		{
			if ( Error::IsFailed(NotifySinkOnEvent(stub, (*iter).second, call)) )
				break;
		}

		spreading_ = false;

		// Remove all pending items
		for ( std::set< unsigned long >::iterator iter = pendingRemoval_.begin() ; pendingRemoval_.end() != iter ; ++iter )
		{	
			UnadviseInternl( *iter );
		}
		pendingRemoval_.clear();

		return _S_OK;
	}

	// Protected tools
	result AccessPointImpl::NotifySinkOnEvent(ICommonRef stub, ICommonRef sink, const Call& call)
	{
		// Check whether sink is still alive.
		if ( !sink )
			return _S_FALSE;
		// Check whether stub is correct.
		if ( !stub )
		{
			// Invoke method directly.
			return sink->Invoke(call);
		}
		// Configure stub.
		stub->SetTarget(sink, false);
		// Translate method with stub.
		return stub->Invoke(call);
	}

	result AccessPointImpl::UnadviseInternl(unsigned long cookie)
	{
		// Check whether sink with specified cookie exists.
		AccessEntries_::iterator iter = accessEntries_.find(cookie);
		if ( iter == accessEntries_.end() )
			return mc::_S_FALSE;
		// Remove sink from map.
		accessEntries_.erase(iter);
		return _S_OK;
	}

}
