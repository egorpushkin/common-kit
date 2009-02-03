#include "Common/Common.h"

#include "EventsSpreader.h"

// TODO: Find stub at the stage of advising sink.

namespace MinCOM
{

	AccessPointImpl::AccessPointImpl(IAccessProviderRef accessProvider, RefGuid iid)
		: CommonImpl< IAccessPoint >()
		, accessProvider_(accessProvider)
		, lock_()
		, iid_(iid)
		, accessEntries_()
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
		CoreMutexLock locker(lock_);

		// Check input arguments for correctness.
		if ( !sink )
			return _E_INVALIDARG;
		// Check whether such sink already advised and
		//  prepare new cookie at the same time.
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
		CoreMutexLock locker(lock_);

		// Check whether sink with specified cookie exists.
		AccessEntries_::iterator iter = accessEntries_.find(cookie);
		if ( iter == accessEntries_.end() )
			return mc::_S_FALSE;
		// Remove sink from map.
		accessEntries_.erase(iter);
		return _S_OK;
	}

	ICommonPtr AccessPointImpl::Find(unsigned long cookie)
	{
		CoreMutexLock locker(lock_);

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

	result AccessPointImpl::Spread(const CallData& call)
	{
		CoreMutexLock locker(lock_);

		// Walk through the entire list of sinks and notify each of them on the event.
		for ( AccessEntries_::iterator iter = accessEntries_.begin() ; accessEntries_.end() != iter ; ++iter )
		{
			if ( Error::IsFailed(NotifySinkOnEvent((*iter).second, call)) )
				return _E_FAIL;
		}
		return _S_OK;
	}

	// Protecetd tools
	result AccessPointImpl::NotifySinkOnEvent(ICommonRef sink, const CallData& call)
	{
		// Create appropriate stub.
		ICommonPtr stub(Object::CreateStub(iid_, sink, false));
		if ( !stub )
		{
			// Invoke methon directly.
			return sink->Invoke(call);
		}
		// Translate method with stub.
		return stub->Invoke(call);
	}

}
