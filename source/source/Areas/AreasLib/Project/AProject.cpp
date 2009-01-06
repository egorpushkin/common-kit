#include "Common/Common.h"

#include "AProject.h"

#include "MsImage.h"

namespace Areas
{

	AProject::AProject()
		: mc::CommonImpl< IAProject >()
		, ContainerImpl_()
		, Components::ObjCounter()
		, image_(IMsImagePtr(mc::ObjectCreator< MsImage >(), IID_IMsImage))
	{
		ContainerImpl_::AdjustEvents(
			AGENTID_ADDINGAREA,
			AGENTID_AREAADDED,
			AGENTID_DELETINGAREA,
			AGENTID_AREADELETED);
	}

	AProject::~AProject()
	{
	}

	// ICommon section
	BEGIN_INTERFACE_MAP(AProject)
		COMMON(IAProject)
		INTERFACE(IAProject)
		IMPL(ContainerImpl_)
	END_INTERFACE_MAP()

	// IAProject section
	IMsImagePtr AProject::GetImage()
	{
		return image_;
	}

	// IItem section
	mc::result AProject::PostInit()
	{
		mc::ItemImpl::Attach(
			mc::CLSID_Commands, 
			mc::ICommonPtr(mc::InstantiateCommands(), mc::IID_ICommon));

		mc::Connect(
			mc::ItemImpl::Acquire(mc::CLSID_Commands),
			ContainerImpl_::GetLocal());

		mc::Connect(
			mc::ICommonPtr(image_, mc::IID_ICommon), 
			ContainerImpl_::GetLocal());

		return mc::_S_OK;
	}

}
