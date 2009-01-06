#ifndef ISERVICEPROVIDER_H__MINCOM__COMMONKIT__INCLUDED_
#define ISERVICEPROVIDER_H__MINCOM__COMMONKIT__INCLUDED_

namespace MinCOM
{
	
	interface IServiceProvider : public ICommon
	{

		virtual ICommonPtr QueryService(RefClsid serviceId) = 0;

	};

	typedef ComPtr< IServiceProvider > IServiceProviderPtr;
	typedef const IServiceProviderPtr& IServiceProviderRef;

	// {be0f487a-b2df-4acd-9c89-d6da2016ac4f} 
	MC_DEFINE_GUID(IID_IServiceProvider, 
	0xbe0f487a, 0xb2df, 0x4acd, 0x9c, 0x89, 0xd6, 0xda, 0x20, 0x16, 0xac, 0x4f);

}

#endif // !ISERVICEPROVIDER_H__MINCOM__COMMONKIT__INCLUDED_
