#ifndef IENUMERATOR_H__CONTAINER__COMMONKIT__INCLUDED_
#define IENUMERATOR_H__CONTAINER__COMMONKIT__INCLUDED_

namespace Container
{

	template 
	<
		class T
	>
	interface IEnumerator : public mc::ICommon
	{

		virtual size_t GetTotal() const = 0;

		virtual bool SelectFirst() = 0;
		virtual bool SelectLast() = 0;
		virtual bool SelectNext() = 0;
		virtual bool SelectPrev() = 0;

		virtual T GetSelected() = 0;
		virtual T GetFirst() = 0;
		virtual T GetLast() = 0;
	    
		virtual const T GetSelected() const = 0;
		virtual const T GetFirst() const = 0;
		virtual const T GetLast() const = 0;

		virtual bool IsValid() const = 0;

	};

	// Common enumerators
	typedef IEnumerator< mc::ICommonPtr > ICommonEnum;

	typedef mc::ComPtr< ICommonEnum > ICommonEnumPtr;
	typedef const ICommonEnumPtr& ICommonEnumRef;

	// {e9148d40-1092-4249-ac4d-11645cffd695} 
	MC_DEFINE_GUID(IID_IEnumerator, 
	0xe9148d40, 0x1092, 0x4249, 0xac, 0x4d, 0x11, 0x64, 0x5c, 0xff, 0xd6, 0x95);

}

#endif // !IENUMERATOR_H__CONTAINER__COMMONKIT__INCLUDED_
