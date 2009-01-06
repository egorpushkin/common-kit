#include "Common/Common.h"

#include "CommonKit/Container.h"

namespace MinCOM
{

	AccessPointImpl::AccessPointImpl()
		: CommonImpl< IAccessPoint >()
		, accessEntries_(Container::CreateUnmanagedMap< AccessEntryPair >())
	{
	}
	
	AccessPointImpl::~AccessPointImpl()
	{
	}

	// ICommon section
	BEGIN_INTERFACE_MAP(AccessPointImpl)
		COMMON(IAccessPoint)
		INTERFACE(IAccessPoint)
	END_INTERFACE_MAP()

	// IAccessPoint section
	result AccessPointImpl::GetAccessId(Iid& iid)
	{
		iid = IID_IAgent;
		return _S_OK;
	}

	IAccessProviderPtr AccessPointImpl::GetAccessProvider()
	{
		return NULL;
	}

	result AccessPointImpl::Advise(ICommonRef sink, unsigned long& cookie)
	{
		// Check whether sink has been already added
		AccessEntryPair entryPair(0, GetWeak(sink));

		Container::MapValueLocator< AccessEntryPair > locator(entryPair);
		Container::ForEach(accessEntries_->Clone(), locator);

		if ( locator.IsFound() )
		{
			cookie = entryPair.first;
			return mc::_S_OK;
		}

		// Add new entry
		return accessEntries_->Add(
			AccessEntryPair(cookie = GenerateUniqueCookie(sink), GetWeak(sink)));
	}

	result AccessPointImpl::Unadvise(unsigned long cookie)
	{		
		return accessEntries_->Delete(AccessEntryPair(cookie, NULL));
	}

	ICommonPtr AccessPointImpl::Query(unsigned long cookie)
	{
		AccessEntryPair entryPair(cookie, NULL);

		Container::MapKeyLocator< AccessEntryPair > locator(entryPair);
		Container::ForEach(accessEntries_->Clone(), locator);

		return GetStrong(entryPair.second);
	}

	IAccessEntriesEnumPtr AccessPointImpl::GetPointsEnum()
	{
		return accessEntries_->Clone();
	}

	// Protected tools
	unsigned long AccessPointImpl::GenerateUniqueCookie(ICommonRef /* sink */)
	{
		unsigned long cookie = 1;

		IAccessEntriesEnumPtr entriesEnum = GetPointsEnum();
		for ( bool hasEntry = entriesEnum->SelectFirst() ; hasEntry ; hasEntry = entriesEnum->SelectNext() )
		{
			if ( entriesEnum->GetSelected().first == cookie )
				++cookie;
		}

		return cookie;
	}

}
