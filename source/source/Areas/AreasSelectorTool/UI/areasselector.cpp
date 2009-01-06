#include "areasselector.h"

#include "AreasSelectorKit/AreasSelectorKit.h"

#include <QFileDialog>
#include <QMessageBox>

AreasSelectorTool::AreasSelectorTool(QWidget *parent, Qt::WFlags flags)
	: QMainWindow(parent, flags)
	, mc::AgentImpl()
	, mc::ItemImpl()
	, ui()
	, project_()
{
	ui.setupUi(this);

	// Disable internal reference counting for this object
	mc::AgentImpl::AddRef();

	// Attach control to McWidget
	ui.selectorControl_->Attach(AreasSelector::CLSID_AreasSelector);

	// Setup menu events
	connect(ui.actionNew_Project, SIGNAL(triggered()), this, SLOT(NewProject()));
	connect(ui.actionLoad_Project, SIGNAL(triggered()), this, SLOT(LoadProject()));
	connect(ui.actionSave_Project, SIGNAL(triggered()), this, SLOT(SaveProject()));
	connect(ui.actionLoad_Image, SIGNAL(triggered()), this, SLOT(LoadImage()));
	connect(ui.actionProperties, SIGNAL(triggered()), this, SLOT(ShowProperties()));
	connect(ui.actionUndo, SIGNAL(triggered()), this, SLOT(Undo()));
	connect(ui.actionRedo, SIGNAL(triggered()), this, SLOT(Redo()));
	connect(ui.actionExit, SIGNAL(triggered()), this, SLOT(close()));

	// Setup shortcuts
	ui.actionUndo->setShortcut(QKeySequence("Ctrl+Z"));
	ui.actionRedo->setShortcut(QKeySequence("Ctrl+Y"));
}

AreasSelectorTool::~AreasSelectorTool()
{
}

// ICommon section
BEGIN_INTERFACE_MAP(AreasSelectorTool)
	IMPL(mc::AgentImpl)
	IMPL(mc::ItemImpl)
END_INTERFACE_MAP()	

// IAgent section
mc::result AreasSelectorTool::Invoke(mc::DispId idMember, mc::DispParamsRef dispParams, mc::IVariantWrapperRef result, mc::RefIid /* iid */)
{
	switch ( idMember )
	{
	case mc::AGENTID_MODIFIEDCHANGED:
		{
			bool modified = dispParams->Get(0)->toBool();

			QString title;

			if ( modified )
			{
				setWindowTitle(tr("Areas Selector Tool *"));
			}
			else
			{
				setWindowTitle(tr("Areas Selector Tool"));
			}
			
		}
		break;
	}

	return mc::_S_OK;
} 

// Private tools
mc::result AreasSelectorTool::UpdateProject(Areas::IAProjectRef project)
{
	// Query for the ISelectorControl interface
	AreasSelector::ISelectorControlPtr areasSelector(ui.selectorControl_->GetCommon(), AreasSelector::IID_ISelectorControl);
	if ( !areasSelector )
		return mc::_E_FAIL;

	// Set loaded project
	areasSelector->SetProject(project);

	// Subscribe on project's events
	unsigned long cookie = 0;
	mc::Advise(mc::ICommonPtr(project, mc::IID_ICommon), mc::ItemImpl::GetLocal(), cookie);

	// Update local reference
	project_ = project;

	return mc::_S_OK;
}

//  Menu events
void AreasSelectorTool::NewProject()
{
	// Instantiate new project
	Areas::IAProjectPtr project(
		Components::InstantiateCommon(Areas::LIBID_Areas, Areas::CLSID_AreasProject),
		Areas::IID_IAProject);

	// Setup new project
	UpdateProject(project);
}

void AreasSelectorTool::LoadProject()
{
	// Select file
	QString fileName = 
		QFileDialog::getOpenFileName(this,
		tr("Load Areas Project"), QString(), tr("Ascii Project File (*.dat)"), NULL /*,
		QFileDialog::DontUseNativeDialog*/); 
	if ( fileName == QString() )
		return;

	// Construct loader
	AreasSelector::ILoaderPtr loader(
		Components::InstantiateCommon(AreasSelector::LIBID_AreasSelector, AreasSelector::CLSID_AsciiLoader),
		AreasSelector::IID_ILoader);
	if ( !loader )
		return;

	// Load project
	Areas::IAProjectPtr project;
	if ( mc::IsFailed(loader->LoadProject(fileName.toAscii().data(), project)) )
	{
		int ret = QMessageBox::critical(this, 
			tr("Areas Selector Tool"),
			tr("Failed to load project."),
			QMessageBox::Ok); 
		return;
	}

	// Setup loaded project
	UpdateProject(project);
}

void AreasSelectorTool::SaveProject()
{
	if ( !project_ )
	{
		int ret = QMessageBox::warning(this, 
			tr("Areas Selector Tool"),
			tr("You must load or create a project first."),
			QMessageBox::Ok); 
		return;
	}

	


}

void AreasSelectorTool::LoadImage()
{
	if ( !project_ )
	{
		int ret = QMessageBox::warning(this, 
			tr("Areas Selector Tool"),
			tr("You must load or create a project first."),
			QMessageBox::Ok); 
		return;
	}

	Areas::IMsImagePtr image = project_->GetImage();
	if ( !project_ )
		return;

	// Select file
	QString fileName = 
		QFileDialog::getOpenFileName(this,
		tr("Load Background Image"), QString(), tr("PGM Image File (*.pgm)"), NULL /*,
		QFileDialog::DontUseNativeDialog*/); 
	if ( fileName == QString() )
		return;

	// Set new image file name
	image->SetSrcName(fileName.toAscii().data());
}

void AreasSelectorTool::ShowProperties()
{
	// Query control for the IAgent
	mc::IAgentPtr selectorAgent(ui.selectorControl_->GetCommon(), mc::IID_IAgent);
	if ( !selectorAgent )
		return;

	// Invoke command
	selectorAgent->Invoke(AreasSelector::AGENTID_DISPLAYPROPERTIES);
}

void AreasSelectorTool::Undo()
{
	mc::IItemPtr projectItem(project_, mc::IID_IItem);
	if ( !projectItem )
		return;

	mc::ICommandsPtr commands(projectItem->Acquire(mc::CLSID_Commands), mc::IID_ICommands);
	if ( !commands )
		return;

	commands->Undo();	
}

void AreasSelectorTool::Redo()
{
	mc::IItemPtr projectItem(project_, mc::IID_IItem);
	if ( !projectItem )
		return;

	mc::ICommandsPtr commands(projectItem->Acquire(mc::CLSID_Commands), mc::IID_ICommands);
	if ( !commands )
		return;

	commands->Redo();	
}