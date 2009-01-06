#ifndef DISPTYPES_H__MINCOM__COMMONKIT__INCLUDED_
#define DISPTYPES_H__MINCOM__COMMONKIT__INCLUDED_

namespace MinCOM
{
	
	typedef long DispId;
	typedef unsigned long LcId;
	typedef unsigned long Dword;

	// Array of disp ids 
	typedef Loki::SmartPtr< 
		DispId,  
		Loki::RefCounted,
		Loki::DisallowConversion,
		Loki::AssertCheck,
		Loki::ArrayStorage
	> DispIdArPtr;	

	typedef const DispIdArPtr& DispIdArRef;

	// DispParams
	//////////////////////////////////////////////////////////////////////////
	class DispParams
	{
	public:

		DispParams(unsigned int count);
		
		result Set(unsigned int index, const Variant& param);

		Variant* Get(unsigned int index);

		Variant& GetRef(unsigned int index);

		unsigned int GetCount();

	private:

		VariantArPtr vararg_;            

		unsigned int countArgs_;            

	};

	// DispParams strong holder
	typedef Loki::SmartPtr< DispParams > DispParamsPtr;
	typedef const DispParamsPtr& DispParamsRef;

	// Creator
	DispParamsPtr CreateParamsCore(unsigned int count);

	// Variant wrapper
	//////////////////////////////////////////////////////////////////////////
	typedef IWrapperT< Variant > IVariantWrapper;
	typedef ComPtr< IVariantWrapper > IVariantWrapperPtr;
	typedef const IVariantWrapperPtr& IVariantWrapperRef;

	IVariantWrapperPtr ConstructVariantWrapper();

	// tagExceptInfo
	//////////////////////////////////////////////////////////////////////////
	typedef struct tagExceptInfo 
	{

	   unsigned short code_; 
	   unsigned short reserved_;
	   String source_;            
	   String description_;      
	   String helpFile_;         
	   unsigned long helpContext_;   
	   void* reservedPtr_;
	   result (*deferredFillIn)(struct tagExceptInfo*);

	} ExceptInfo;

	// ExceptInfo strong holder
	typedef Loki::SmartPtr< ExceptInfo > ExceptInfoPtr;
	typedef const ExceptInfoPtr& ExceptInfoRef;

	// {687122e8-dafa-4ad6-b38c-e2db05dfce15} 
	MC_DEFINE_GUID(IID_Common, 
	0x687122e8, 0xdafa, 0x4ad6, 0xb3, 0x8c, 0xe2, 0xdb, 0x05, 0xdf, 0xce, 0x15);

	// {a472023e-d6d8-4556-936b-f3969ac46b90} 
	MC_DEFINE_GUID(CLSID_This, 
	0xa472023e, 0xd6d8, 0x4556, 0x93, 0x6b, 0xf3, 0x96, 0x9a, 0xc4, 0x6b, 0x90);

}

#endif // !DISPTYPES_H__MINCOM__COMMONKIT__INCLUDED_
