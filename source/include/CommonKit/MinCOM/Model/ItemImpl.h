#ifndef ITEMIMPL_H__MINCOM__COMMONKIT__INCLUDED_
#define ITEMIMPL_H__MINCOM__COMMONKIT__INCLUDED_

namespace MinCOM
{

	class ItemImpl 
		: public CommonImpl< IItem > 
	{
	public:

		ItemImpl();

		// IItem section
		virtual result SetParent(ICommonRef parent);

		virtual ICommonPtr GetParent();

		virtual bool HasParent();

		virtual result SetLocal(ICommonRef local);

		virtual ICommonPtr GetLocal();

		virtual result Attach(RefIid toolId, ICommonRef tool, bool strong = true);

		virtual result Remit(RefIid toolId);

		virtual ICommonPtr Acquire(RefIid toolId);

		virtual result PostInit();

		// ICommon section
		DECLARE_INTERFACE_MAP()		

	protected:

		template 
		< class T >
		static result SetParent(const T& item, ICommonRef parent);

	private:

		// Parent connection tools
		ICommonPtr AcquireFromParent(RefIid toolId);

	private:

		ICommonWeak parent_;

		ICommonWeak local_;

		ToolsContainer< ICommonPtr > toolsS_;

		ToolsContainer< ICommonWeak > toolsW_;

	};

}

#include "ItemImpl_template.h"

#endif // !ITEMIMPL_H__MINCOM__COMMONKIT__INCLUDED_
