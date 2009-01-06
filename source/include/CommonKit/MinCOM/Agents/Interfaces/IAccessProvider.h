#ifndef IACCESSPROVIDER_H__MINCOM__COMMONKIT__INCLUDED_
#define IACCESSPROVIDER_H__MINCOM__COMMONKIT__INCLUDED_

namespace MinCOM
{

	interface IAccessProvider : public ICommon
	{

		virtual result AdviseAccessPoint(
			RefIid iid, 
			IAccessPointRef accessPoint,
			bool replace) = 0;

		virtual result UnadviseAccessPoint(
			RefIid iid) = 0;

		virtual result FindAccessPoint(
			RefIid iid, 
			IAccessPointPtr& accessPoint) = 0;

	};

	typedef ComPtr< IAccessProvider > IAccessProviderPtr;
	typedef ComPtr< IAccessProvider, false > IAccessProviderWeak;

	typedef const IAccessProviderPtr& IAccessProviderRef;
	typedef const IAccessProviderWeak& IAccessProviderWeakRef;

	// {b3bbe3e0-d18d-4949-b9ce-7610a75babab} 
	MC_DEFINE_GUID(IID_IAccessProvider, 
	0xb3bbe3e0, 0xd18d, 0x4949, 0xb9, 0xce, 0x76, 0x10, 0xa7, 0x5b, 0xab, 0xab);

}

#endif // !IACCESSPROVIDER_H__MINCOM__COMMONKIT__INCLUDED_
