#include "qexttest001.h"

#include "AreasSelectorKit/AreasSelectorKit.h"

QExtTest001::QExtTest001(QWidget *parent, Qt::WFlags flags)
	: QMainWindow(parent, flags)
{
	ui.setupUi(this);

	ui.selectorDemo_->Attach(AreasSelector::LIBID_AreasSelector, AreasSelector::CLSID_AreasSelector);

	// Create project
	AreasSelector::ILoaderPtr loader(
		Components::InstantiateCommon(AreasSelector::LIBID_AreasSelector, AreasSelector::CLSID_AsciiLoader),
		AreasSelector::IID_ILoader);
	if ( !loader )
		return;

	if ( mc::IsFailed(loader->LoadProject(mc::StringA("./Fragment1Areas.dat"), project_)) )
		return;

	Areas::IMsImagePtr projectImage = project_->GetImage();	
	projectImage->SetSrcName(mc::StringA("./Fragment1.pgm"));

	AreasSelector::ISelectorControlPtr areasSelector(ui.selectorDemo_->GetCommon(), AreasSelector::IID_ISelectorControl);
	if ( !areasSelector )
		return;

	areasSelector->SetProject(project_);
}

QExtTest001::~QExtTest001()
{

}
