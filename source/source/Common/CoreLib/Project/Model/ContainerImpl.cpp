#include "Common/Common.h"

#include "CommonKit/Project.h"

#include "Project/Commands/AddRollback.h"

#include "Project/Commands/DeleteRollback.h"

namespace Project
{

	ContainerImpl::ContainerImpl()
		: mc::CommonImpl< IContainer >()
		, mc::APImpl()
		, mc::AgentImpl()
		, mc::CookiesHelper()
		, CEvImpl()
		, items_(Container::CreateUnmanagedDefault< ComPtr_ >())
	{
	}

	// ICommon section
	BEGIN_INTERFACE_MAP(ContainerImpl)
		COMMON(IContainer)
		INTERFACE_(IContainer, IID_IContainer)
		IMPL(mc::APImpl)
		IMPL(mc::AgentImpl)
		IMPL(CEvImpl)
	END_INTERFACE_MAP()

	// IArea section	
	mc::result ContainerImpl::Add(ComRef_ item)
	{
		// Notify on adding item
		if ( mc::IsFailed(OnBeforeOp(item, CEvImpl::GetOnBeforeAdd())) )
			return mc::_E_CANCELED;

		// Register item locally
		items_->Add(item);

		// Configure item after adding
		return DoAdd(item);
	}

	mc::result ContainerImpl::InsertAfter(ComRef_ item, ComRef_ src)
	{
		// Notify on adding item
		if ( mc::IsFailed(OnBeforeOp(item, CEvImpl::GetOnBeforeAdd())) )
			return mc::_E_CANCELED;

		// Register item locally
		items_->InsertAfter(item, src);

		// Configure item after adding
		return DoAdd(item);
	}
	
	mc::result ContainerImpl::InsertAfter(ComRef_ item, unsigned int index)
	{
		// Notify on adding item
		if ( mc::IsFailed(OnBeforeOp(item, CEvImpl::GetOnBeforeAdd())) )
			return mc::_E_CANCELED;

		// Register item locally
		items_->InsertAfter(item, index);

		// Configure item after adding
		return DoAdd(item);
	}

	mc::result ContainerImpl::Delete(ComRef_ item)
	{
		size_t index = 0;
		
		try
		{
			index = items_->Where(item);
		}
		catch ( ... )
		{
			return mc::_E_INVALIDARG;
		}

		return DeleteCore(item, index);
	}
	
	mc::result ContainerImpl::Delete(unsigned int index)
	{
		ComPtr_ item;

		try
		{
			if ( !(item = items_->GetAt(index)) )
				throw std::exception();
		}
		catch ( ... )
		{
			return mc::_E_INVALIDARG;
		}

		return DeleteCore(item, index);
	}

	mc::result ContainerImpl::Clear()
	{
		if ( mc::IsFailed(OnBeforeClear()) )
			return mc::_E_CANCELED;

		while ( items_->Size() > 0 )
		{
			// Acquire item
			ComPtr_ item = items_->Clone()->GetFirst();

			// Delete item locally
			items_->Delete(item);

			// Delete each element correctly
			DoDelete(item, 0);
		}

		// Notify on container cleared
		OnWhenCleared();

		return mc::_S_OK;
	}

	ContainerImpl::IEnumPtr_ ContainerImpl::GetItems()
	{
		return items_->Clone();
	}

	// IAgent section
	mc::result ContainerImpl::Invoke(mc::DispId idMember, mc::DispParamsRef dispParams, mc::IVariantWrapperRef /* result */, mc::RefIid /* iid */)
	{
		// Check whether one of local methods invoked
		//  if ( AGENTID_CONTAINER_METHOD1 == idMember )
		//  {
		//		// ...
		//  }
		//  // ...

		return mc::APImpl::SpreadBase(idMember, dispParams);
	}

	// Protected events tools
	void ContainerImpl::AdjustEvents(mc::DispId beforeAdd, mc::DispId added, mc::DispId beforeDelete, mc::DispId deleted)
	{	
		CEvImpl::SetOnBeforeAdd(beforeAdd);
		CEvImpl::SetOnAfterAdd(added);
		CEvImpl::SetOnBeforeDelete(beforeDelete);
		CEvImpl::SetOnAfterDelete(deleted);
	}

	// Core tools
	mc::result ContainerImpl::DeleteCore(ComRef_ item, size_t index)
	{
		// Notify on deleting item
		if ( mc::IsFailed(OnBeforeOp(item, CEvImpl::GetOnBeforeDelete())) )
			return mc::_E_CANCELED;

		// Delete item locally
		items_->Delete(item);

		// Configure item after deleting
		return DoDelete(item, index);
	}

	// Private add / remove tools	
	mc::result ContainerImpl::DoAdd(ComRef_ item)
	{
		if ( !item )
			return mc::_E_INVALIDARG;

		// Register add rollback command
		RegisterAddRollback(item);

		// Try to modify item's parent
		mc::ItemImpl::SetParent(item, mc::ItemImpl::GetLocal());

		// Advise events listener to added item
		LocalAdvise(item);

		// Notify on item added
		OnAfterOp(item, CEvImpl::GetOnAfterAdd());

		return mc::_S_OK;
	}
	
	mc::result ContainerImpl::DoDelete(ComRef_ item, size_t index)
	{
		if ( !item )
			return mc::_E_INVALIDARG;

		// Register delete rollback command
		RegisterDeleteRollback(item, index);

		// Skip parent 
		mc::ItemImpl::SetParent(item, NULL);

		// Unadvise events listener to added item
		LocalUnadvise(item);

		// Notify on item deleted
		OnAfterOp(item, CEvImpl::GetOnAfterDelete());
		
		return mc::_S_OK;
	}

	// Event dispatchers	
	mc::result ContainerImpl::OnBeforeOp(ComRef_ item, mc::DispId id)
	{
		bool cancel = false;
		mc::result code = mc::APImpl::SpreadBase(
			id, 
			mc::CreateParams(
				mc::ItemImpl::GetLocal(),					// Param1: Container
				item,										// Param2: Item
				&cancel));									// Param3: Cancellation

		if ( mc::IsFailed(code) || cancel )
			return mc::_E_FAIL;

		return mc::_S_OK;
	}
	
	mc::result ContainerImpl::OnAfterOp(ComRef_ item, mc::DispId id)
	{
		return mc::APImpl::SpreadBase(
			id, 
			mc::CreateParams(
				mc::ItemImpl::GetLocal(),					// Param1: Container
				item));										// Param2: Item
	}


	mc::result ContainerImpl::OnBeforeClear()
	{
		bool cancel = false;
		mc::result code = mc::APImpl::SpreadBase(
			AGENTID_BEFORECLEAR, 
			mc::CreateParams(
				mc::ItemImpl::GetLocal(),					// Param1: Container
				&cancel));									// Param2: Cancellation

		if ( mc::IsFailed(code) || cancel )
			return mc::_E_FAIL;

		return mc::_S_OK;
	}

	mc::result ContainerImpl::OnWhenCleared()
	{
		return mc::APImpl::SpreadBase(
			AGENTID_CLEARED, 
			mc::CreateParams(
				mc::ItemImpl::GetLocal()));					// Param1: Container
	}

	// Commands
	mc::result ContainerImpl::RegisterAddRollback(ComRef_ item)
	{
		mc::ICommandPtr command = mc::InstantiateCommand< AddRollback >(
			CreateParams(
				GetLocal(), 
				item));
		if ( !command )
			return mc::_E_FAIL;

		mc::ICommandsPtr commands(mc::APImpl::Acquire(mc::CLSID_Commands), mc::IID_ICommands);
		if ( !commands )
			return mc::_S_FALSE;

		return commands->Add(command);
	}

	mc::result ContainerImpl::RegisterDeleteRollback(ComRef_ item, size_t index)
	{
		mc::ICommandPtr command = mc::InstantiateCommand< DeleteRollback >(
			CreateParams(
				GetLocal(), 
				item,
				(unsigned int)index));
		if ( !command )
			return mc::_E_FAIL;

		mc::ICommandsPtr commands(mc::APImpl::Acquire(mc::CLSID_Commands), mc::IID_ICommands);
		if ( !commands )
			return mc::_S_FALSE;

		return commands->Add(command);
	}

}