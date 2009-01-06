#include "areasselector.h"

#include "Serialization/AsciiAreas.h"

AreasSelector::AreasSelector(QWidget *parent, Qt::WFlags flags)
	: QDialog(parent, flags)
{
	ui.setupUi(this);

	ConfigureProject();

	selectorCommon_ = mc::ICommonPtr(ui.selector_, mc::IID_ICommon);
	ui.selector_->SetLocal(selectorCommon_);
	ui.selector_->SetProject(project_);

	selectorMirrorCommon_ = mc::ICommonPtr(ui.selectorMirror_, mc::IID_ICommon);
	ui.selectorMirror_->SetLocal(selectorMirrorCommon_);
	ui.selectorMirror_->SetProject(project_);
}

AreasSelector::~AreasSelector()
{
}

mc::result AreasSelector::ConfigureProject()
{
	Serialization::AsciiAreas areasLoader;
	if ( mc::IsFailed(areasLoader.LoadProject(mc::StringA("./Auto9.dat"), project_)) )
	//if ( mc::IsFailed(areasLoader.LoadProject(mc::StringA("./Fragment1Areas.dat"), project_)) )
	//if ( mc::IsFailed(areasLoader.LoadProject(mc::StringA("./Chernobyl.dat"), project_)) )
		return mc::_E_FAIL;

	Areas::IMsImagePtr projectImage = project_->GetImage();
	//projectImage->SetSrcName(mc::StringA("./p182r24_4t19880528_nn4_f.pgm"));
	projectImage->SetSrcName(mc::StringA("./Fragment1.pgm"));

	return mc::_S_OK;
}
