#ifndef ITYPEINFO_H__MINCOM__COMMONKIT__INCLUDED_
#define ITYPEINFO_H__MINCOM__COMMONKIT__INCLUDED_

namespace MinCOM
{

	interface ITypeInfo : public ICommon
	{
	};

	typedef ComPtr< ITypeInfo > ITypeInfoPtr;
	typedef ComPtr< ITypeInfo, false > ITypeInfoWeak;

	typedef const ITypeInfoPtr& ITypeInfoRef;

	// {c529b3a0-bbbb-4656-9c13-322837b40fe3} 
	MC_DEFINE_GUID(IID_ITypeInfo, 
	0xc529b3a0, 0xbbbb, 0x4656, 0x9c, 0x13, 0x32, 0x28, 0x37, 0xb4, 0x0f, 0xe3);

}

#endif // !ITYPEINFO_H__MINCOM__COMMONKIT__INCLUDED_
