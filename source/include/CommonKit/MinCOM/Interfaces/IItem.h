#ifndef IITEM_H__MINCOM__COMMONKIT__INCLUDED_
#define IITEM_H__MINCOM__COMMONKIT__INCLUDED_

namespace MinCOM
{

	interface IItem : public ICommon
	{
		
		virtual result SetParent(ICommonRef parent) = 0;

		virtual ICommonPtr GetParent() = 0;
		 
		virtual bool HasParent() = 0;

		virtual result SetLocal(ICommonRef local) = 0;

		virtual ICommonPtr GetLocal() = 0;

		virtual result Attach(RefIid toolId, ICommonRef tool, bool strong = true) = 0;

		virtual result Remit(RefIid toolId) = 0;

		virtual ICommonPtr Acquire(RefIid toolId) = 0;

		virtual result PostInit() = 0;

	};

	typedef ComPtr< IItem > IItemPtr;
	typedef ComPtr< IItem, false > IItemWeak;

	typedef const IItemPtr& IItemRef;
	typedef const IItemWeak& IItemWeakRef;

	// {e10851b1-9e89-4d4c-9bb7-088af613d587} 
	MC_DEFINE_GUID(IID_IItem, 
	0xe10851b1, 0x9e89, 0x4d4c, 0x9b, 0xb7, 0x08, 0x8a, 0xf6, 0x13, 0xd5, 0x87);

}

#endif // !IITEM_H__MINCOM__COMMONKIT__INCLUDED_
