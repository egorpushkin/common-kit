#include "Common/Common.h"

#include "CommonKit/Container.h"

namespace MinCOM
{

	AccessProviderImpl::AccessProviderImpl(bool regDefault)
		: CommonImpl< IAccessProvider >()
		, ItemImpl()
		, accessPoints_(Container::CreateUnmanagedMap< AccessPointPair >())
	{
		if ( regDefault )
			RegisterAccessPoint(IID_IAgent);
	}

	AccessProviderImpl::~AccessProviderImpl()
	{
	}

	// ICommon section
	BEGIN_INTERFACE_MAP(AccessProviderImpl)
		COMMON(IAccessProvider)
		INTERFACE(IAccessProvider)
		IMPL(ItemImpl)
	END_INTERFACE_MAP()

	// IAccessProvider section
	result AccessProviderImpl::AdviseAccessPoint(RefIid iid, IAccessPointRef accessPoint, bool replace)
	{
		if ( !accessPoint )
			return _E_INVALIDARG;

		if ( ( accessPoints_->Find(AccessPointPair(iid, NULL))->IsValid() ) && !replace )
			return _E_FAIL;

		accessPoints_->Add(AccessPointPair(iid, accessPoint));

		return _S_OK;
	}

	result AccessProviderImpl::UnadviseAccessPoint(RefIid iid)
	{
		return accessPoints_->Delete(AccessPointPair(iid, NULL));
	}

	result AccessProviderImpl::FindAccessPoint(RefIid iid, IAccessPointPtr& accessPoint)
	{
		AccessPointPair pointPair(iid, NULL);

		Container::MapKeyLocator< AccessPointPair > locator(pointPair);
		Container::ForEach(accessPoints_->Clone(), locator);

		if ( locator.IsFound() )
			accessPoint = pointPair.second;

		return ( locator.IsFound() ? _S_OK : _S_FALSE );
	}

	// Public events tools
	result AccessProviderImpl::SpreadEventCore(IAccessEntriesEnumRef entries, DispSpreader& spreader)
	{
		// Spread event
		ForEach(entries, spreader);

		// Return error code
		return spreader.GetLastError();
	}

	// Protected tools
	IAccessPointPtr AccessProviderImpl::GetAccessPoint(RefIid iid)
	{
		IAccessPointPtr accessPoint;
		
		if ( FindAccessPoint(iid, accessPoint) != _S_OK )
			return NULL;

		return accessPoint;
	}

	IAccessEntriesEnumPtr AccessProviderImpl::GetAccessEntries(RefIid iid)
	{
		IAccessPointPtr accessPoint = GetAccessPoint(iid);
		if ( !accessPoint )
			return NULL;
		
		return accessPoint->GetPointsEnum();
	}

	result AccessProviderImpl::RegisterAccessPoint(RefIid iid, bool replace)
	{
		return AdviseAccessPoint(
			iid, 
			IAccessPointPtr(mc::ObjectCreator< AccessPointImpl >(), IID_IAccessPoint), 
			replace);
	}

	// Protected events tools
	result AccessProviderImpl::SpreadBase(DispId id, mc::DispParamsRef params, RefIid iid /* = mc::IID_IAgent */)
	{
		return SpreadEvent< DispSpreader >(id, params, iid);
	}

}
