#include "Common/Common.h"

#include "MsImage.h"

#include "Commands/ImageName.h"

namespace Areas
{

	MsImage::MsImage()
		: mc::CommonImpl< IMsImage >()
		, mc::APImpl()
		, Components::ObjCounter()
		, srcName_()
	{
	}

	MsImage::~MsImage()
	{
	}

	// ICommon section
	BEGIN_INTERFACE_MAP(MsImage)
		COMMON(IMsImage)
		INTERFACE(IMsImage)
		IMPL(mc::APImpl)
	END_INTERFACE_MAP()

	// Areas::IMsImage section
	mc::result MsImage::SetSrcName(const mc::StringA& imageSrc)
	{
		RegisterNameCommand(srcName_);

		srcName_ = imageSrc;

		return OnSrcNameChanged();
	}

	mc::StringA MsImage::GetSrcName()
	{
		return srcName_;
	}

	// Event dispatchers
	mc::result MsImage::OnSrcNameChanged()
	{
		return mc::APImpl::SpreadBase(
			AGENTID_IMGCHANGED, 
			CreateParams(
				mc::ItemImpl::GetLocal()));
	}

	// Commands
	mc::result MsImage::RegisterNameCommand(const mc::StringA& name)
	{
		mc::ICommandPtr command = mc::InstantiateCommand< ImageName >(
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
