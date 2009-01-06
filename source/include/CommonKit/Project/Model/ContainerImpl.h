#ifndef CONTAINERIMPL_H__PROJECTKIT__INCLUDED_
#define CONTAINERIMPL_H__PROJECTKIT__INCLUDED_

namespace Project
{

	class ContainerImpl
		: public mc::CommonImpl< IContainer > 
		, public mc::APImpl
		, public mc::AgentImpl
		, public mc::CookiesHelper
		, public CEvImpl
	{
	protected:

		typedef mc::ICommonPtr ComPtr_;

		typedef Container::ICommonsPtr IContPtr_;

	public:

		ContainerImpl();

		// ICommon section
		DECLARE_INTERFACE_MAP()

		// IContainer section
		virtual mc::result Add(ComRef_ item);

		virtual mc::result InsertAfter(ComRef_ item, ComRef_ src);

		virtual mc::result InsertAfter(ComRef_ item, unsigned int index);

		virtual mc::result Delete(ComRef_ item);

		virtual mc::result Delete(unsigned int index);

		virtual mc::result Clear();

		virtual IEnumPtr_ GetItems();

		// IAgent section
		virtual mc::result Invoke(mc::DispId idMember, mc::DispParamsRef dispParams, mc::IVariantWrapperRef result, mc::RefIid iid);

	protected:

		// Protected events tools
		void AdjustEvents(
			mc::DispId beforeAdd, 
			mc::DispId added, 
			mc::DispId beforeDelete, 
			mc::DispId deleted);

		// Events' registration
		template 
		< class U >
		mc::result LocalAdvise(
			const U& connectee, 
			mc::RefIid apIid = mc::IID_IAgent);

		template 
		< class U >
		mc::result LocalUnadvise(
			const U& connectee, 
			mc::RefIid apIid = mc::IID_IAgent);

	private:

		// Core tools
		mc::result DeleteCore(ComRef_ item, size_t index);

		// Private add / delete tools
		mc::result DoAdd(ComRef_ item);

		mc::result DoDelete(ComRef_ item, size_t index);

	private:

		// Event dispatchers
		mc::result OnBeforeOp(ComRef_ item, mc::DispId id);
		
		mc::result OnAfterOp(ComRef_ item, mc::DispId id);

		mc::result OnBeforeClear();

		mc::result OnWhenCleared();

		// Commands
		mc::result RegisterAddRollback(ComRef_ item);

		mc::result RegisterDeleteRollback(ComRef_ item, size_t index);
			
	private:
	
		// Points container
		IContPtr_ items_;		

	};

}

#include "ContainerImpl_template.h"

#endif // !CONTAINERIMPL_H__PROJECTKIT__INCLUDED_
