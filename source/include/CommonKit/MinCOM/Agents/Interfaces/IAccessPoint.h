#ifndef IACCESSPOINT_H__MINCOM__COMMONKIT__INCLUDED_
#define IACCESSPOINT_H__MINCOM__COMMONKIT__INCLUDED_

namespace MinCOM
{

	// Required declaration
	interface IAccessProvider;
	typedef ComPtr< IAccessProvider > IAccessProviderPtr;

	// Access entry requirements
	typedef Container::IContainer< AccessEntryPair > IAccessEntries;
	typedef Container::IEnumerator< AccessEntryPair > IAccessEntriesEnum;

	typedef ComPtr< IAccessEntries > IAccessEntriesPtr;
	typedef ComPtr< IAccessEntriesEnum > IAccessEntriesEnumPtr;
	typedef const IAccessEntriesEnumPtr& IAccessEntriesEnumRef;

	interface IAccessPoint : public ICommon
	{

		virtual result GetAccessId(Iid& iid) = 0;

		virtual IAccessProviderPtr GetAccessProvider() = 0;

		virtual result Advise(ICommonRef sink, unsigned long& cookie) = 0;

		virtual result Unadvise(unsigned long cookie) = 0;

		virtual ICommonPtr Query(unsigned long cookie) = 0;

		virtual IAccessEntriesEnumPtr GetPointsEnum() = 0;

	};

	// Smart pointers
	typedef ComPtr< IAccessPoint > IAccessPointPtr;
	typedef const IAccessPointPtr& IAccessPointRef;

	typedef ComPtr< IAccessPoint, false > IAccessPointWeak;
	typedef const IAccessPointWeak& IAccessPointWeakRef;

	// Containers
	typedef std::pair< Guid, IAccessPointPtr > AccessPointPair;

	typedef Container::IContainer< AccessPointPair > IAccessPoints;
	typedef Container::IEnumerator< AccessPointPair > IAccessPointsEnum;
	
	// Containers' pointers
	typedef ComPtr< IAccessPoints > IAccessPointsPtr;
	typedef const IAccessPointsPtr& IAccessPointsRef;
	
	typedef ComPtr< IAccessPointsEnum > IAccessPointsEnumPtr;
	typedef const IAccessPointsEnumPtr& IAccessPointsEnumRef;

	// {f2df16f9-16ca-41e8-b73b-6643b5700144} 
	MC_DEFINE_GUID(IID_IAccessPoint, 
	0xf2df16f9, 0x16ca, 0x41e8, 0xb7, 0x3b, 0x66, 0x43, 0xb5, 0x70, 0x01, 0x44);

}

#endif // !IACCESSPOINT_H__MINCOM__COMMONKIT__INCLUDED_
