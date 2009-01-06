#include "Common/Common.h"

#include "CommonKit/Project.h"

namespace MinCOM
{

	ItemImpl::ItemImpl()
		: mc::CommonImpl< IItem >()
		, parent_()
		, local_()
		, toolsS_()
		, toolsW_()
	{
	}

	// ICommon section
	BEGIN_INTERFACE_MAP(ItemImpl)
		COMMON(IItem)
		INTERFACE(IItem)
	END_INTERFACE_MAP()

	// IItem section
	mc::result ItemImpl::SetParent(mc::ICommonRef parent)
	{
		parent_ = GetWeak(parent);
		return mc::_S_OK;
	}

	mc::ICommonPtr ItemImpl::GetParent()
	{
		return GetStrong(parent_);
	}

	bool ItemImpl::HasParent()
	{
		if ( !parent_ )
			return false;

		mc::ICommonPtr strongParent = GetStrong(parent_);
		if ( !strongParent )
			return false;

		return true;
	}

	mc::result ItemImpl::SetLocal(mc::ICommonRef local)
	{
		local_ = GetWeak(local);

		return mc::_S_OK;
	}

	mc::ICommonPtr ItemImpl::GetLocal()
	{
		return GetStrong(local_);
	}

	result ItemImpl::Attach(RefIid toolId, ICommonRef tool, bool strong /* = true */)
	{
		if ( strong )
			return toolsS_.Attach(toolId, tool);
		else
			return toolsW_.Attach(toolId, GetWeak(tool));
	}

	result ItemImpl::Remit(RefIid toolId)
	{
		toolsS_.Remit(toolId);
		
		toolsW_.Remit(toolId);

		return _S_OK;
	}

	ICommonPtr ItemImpl::Acquire(RefIid toolId)
	{
		ICommonPtr tool = toolsS_.Acquire(toolId);
		if ( tool )
			return tool;

		tool = GetStrong(toolsW_.Acquire(toolId));
		if ( tool )
			return tool;

		return AcquireFromParent(toolId);
	}

	result ItemImpl::PostInit()
	{
		return _E_NOTIMPL;
	}

	// Parent connection tools
	ICommonPtr ItemImpl::AcquireFromParent(RefIid toolId)
	{
		// Check whether parent is still available
		ICommonPtr cmnParent(GetParent());
		if ( !cmnParent )
			return NULL;

		// Acquire IItem control from parent 
		IItemPtr parentItem(cmnParent, IID_IItem);
		if ( !parentItem )
			return NULL;

		// Try to acquire required object from parent's collection
		return parentItem->Acquire(toolId);
	}

}
