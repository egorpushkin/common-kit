#include "Common/Common.h"

#include "Area.h"

#include "Commands/AreaName.h"

namespace Areas
{

	Area::Area()
		: mc::CommonImpl< IArea >()
		, ContainerImpl_()
		, Components::ObjCounter()
		, name_()
	{
		ContainerImpl_::AdjustEvents(
			AGENTID_ADDINGPOINT,
			AGENTID_POINTADDED,
			AGENTID_DELETINGPOINT,
			AGENTID_POINTDELETED);
	}

	Area::~Area()
	{
	}

	// ICommon section
	BEGIN_INTERFACE_MAP(Area)
		COMMON(IArea)
		INTERFACE(IArea)
		IMPL(ContainerImpl_)
	END_INTERFACE_MAP()

	// IArea section
	void Area::SetName(const mc::StringA& name)
	{
		// Register command (required for undo support)
		RegisterAreaNameCommand(name_);

		// Modify object
		name_ = name;

		// Notify sinks
		OnNameChanged(name_);
	}

	mc::StringA Area::GetName()
	{
		return name_;
	}

	// Event dispatchers
	mc::result Area::OnNameChanged(const mc::StringA& name)
	{
		return mc::APImpl::SpreadBase(
			AGENTID_AREANAMECHANGED, 
			CreateParams(
				mc::ItemImpl::GetLocal(),
				name));
	}

	// Commands
	mc::result Area::RegisterAreaNameCommand(const mc::StringA& name)
	{
		mc::ICommandPtr command = mc::InstantiateCommand< AreaName >(
			mc::CreateParams(
				mc::ItemImpl::GetLocal(), 
				name));
		if ( !command )
			return mc::_E_FAIL;

		mc::ICommandsPtr commands(mc::ItemImpl::Acquire(mc::CLSID_Commands), mc::IID_ICommands);
		if ( !commands )
			return mc::_S_FALSE;

		return commands->Add(command);
	}	

}
