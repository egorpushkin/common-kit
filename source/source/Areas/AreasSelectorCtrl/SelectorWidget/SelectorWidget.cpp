#include <QtGui>

#include "SelectorWidget.h"

#include "Spirits/DefaultBehaviour.h"

#include "SelectorPainter.h"

SelectorWidget::SelectorWidget(QWidget* parent)
	: QAbstractScrollArea(parent)
	, mc::CommonImpl< AreasSelector::ISelectorControl >()
	, mc::APImpl()
	, mc::AgentImpl()
	, AreasSelector::WidgetImpl()
	, QExtension::QWidgetImpl()
	, Components::ObjCounter()
	, project_()
	, pImage_(NULL)
	, cartesians_()
{
}

SelectorWidget::~SelectorWidget()
{
	delete pImage_;
}

// ICommon section
BEGIN_INTERFACE_MAP(SelectorWidget)
	COMMON(AreasSelector::ISelectorControl)
	INTERFACE_(AreasSelector::ISelectorControl, AreasSelector::IID_ISelectorControl)
	IMPL(mc::APImpl)
	IMPL(mc::AgentImpl)
	IMPL(AreasSelector::WidgetImpl)
	IMPL(QExtension::QWidgetImpl)
END_INTERFACE_MAP()

// ISelectorWidget section
mc::result SelectorWidget::SetProject(Areas::IAProjectRef project)
{
	if ( project_ )
	{
		// Unadvise sink from project
	}

	project_ = project;

	if ( project_ )
	{
		// Subscribe on project's events
		unsigned long cookie = 0;
		mc::Advise(mc::ICommonPtr(project_, mc::IID_ICommon), mc::APImpl::GetLocal(), cookie);
	}

	// Reconfigure internal image representation and selector settings (scroll bars, etc.)
	UpdateImage();

	// Notify all sinks on new project
	OnProjectChanged();

	// Update content
	viewport()->update();

	return mc::_S_OK;
}

Areas::IAProjectPtr SelectorWidget::GetProject()
{
	return project_;
}

// IAgent section
mc::result SelectorWidget::Invoke(mc::DispId idMember, mc::DispParamsRef dispParams, mc::IVariantWrapperRef resultRefIid /* iid */, mc::RefIid /* iid *//* = IID_IAgent */)
{
	switch ( idMember )
	{
		case Areas::AGENTID_IMGCHANGED:
		{
			UpdateImage();
			viewport()->update();
		}
		break;
		case AreasSelector::AGENTID_DISPLAYPROPERTIES:
		{
			mc::APImpl::SpreadBase(idMember, dispParams);
		}
		case Areas::AGENTID_AREAADDED:
		case Areas::AGENTID_AREADELETED:
		case Areas::AGENTID_AREANAMECHANGED:
		case Areas::AGENTID_POINTADDED:
		case Areas::AGENTID_POINTDELETED:
		case Areas::AGENTID_LOCATIONCHANGED:
		case mc::AGENTID_MODIFIEDCHANGED:
		{
			viewport()->update();			
		}
		break;
	}

	return mc::_S_OK;
}

// IItem section
mc::result SelectorWidget::PostInit()
{
	// Setup behaviour
	WidgetImpl::SetBehaviour(
		AreasSelector::IBehaviourPtr(
			mc::ObjectCreator< AreasSelector::DefaultBehaviour >(), 
			AreasSelector::IID_IBehaviour));

	// Configure behaviour
	mc::ICommonPtr local = mc::APImpl::GetLocal();
	AreasSelector::IBehaviourPtr behaviour = AreasSelector::WidgetImpl::GetBehaviour();

	if ( !local || !behaviour )
		return mc::_E_FAIL;

	// Advise behaviour object on selector's events
	unsigned long cookie = 0;
	mc::Advise(local, mc::ICommonPtr(behaviour, mc::IID_ICommon), cookie);

	// Setup parent for current behaviour
	mc::IItemPtr behaviourItem(behaviour, mc::IID_IItem);
	if ( behaviourItem )
	{
		behaviourItem->SetParent(local);
	}

	return mc::_S_OK;
}

// Handlers
void SelectorWidget::UpdateImage()
{
	if ( pImage_ )
	{
		// Destroy current image
		delete pImage_;
		pImage_ = NULL;

		ConfigureScrollBars();
	}

	if ( !project_ )
		// Do nothing if no project specified
		return;

	// Acquire project image
	Areas::IMsImagePtr projectImage = project_->GetImage();
	if ( !projectImage )
		return;

	// Acquire image name
	mc::StringA imgSrcName(projectImage->GetSrcName());

	// Construct new image representation for local use
	pImage_ = new QImage(imgSrcName.c_str(), "PGM");
	
	// Check whether image construction failed
	if ( pImage_->isNull() ) 
	{
		// Destroy image
		delete pImage_;
		pImage_ = NULL;

		ConfigureScrollBars();

		return;
	}

	// Configure viewport
	cartesians_.Reset();

	ConfigureScrollBars();
}

// Event dispatchers
mc::result SelectorWidget::OnProjectChanged()
{
	return mc::APImpl::SpreadBase(
		AreasSelector::AGENTID_PROJECTCHANGED, 
		CreateParams(mc::ItemImpl::GetLocal()));
}

// Gui handlers
void SelectorWidget::paintEvent(QPaintEvent*)
{
	// Construct painter
	QPainter painter(viewport());

	// Configure painter
	AreasSelector::SelectorPainter::ConfigurePainter(painter);

	// Draw background image
	AreasSelector::SelectorPainter::DrawBackground(painter, *this);
	
	// Draw content via behaviour
	AreasSelector::IBehaviourPtr behaviour = WidgetImpl::GetBehaviour();
	if ( !behaviour )
		return;

	behaviour->OnPaint(painter);		
}

void SelectorWidget::resizeEvent(QResizeEvent* event)
{
	cartesians_.SetViewport(viewport()->width(), viewport()->height());

	// TODO: Check whether this call works properly here
	// No!!!!
	ConfigureScrollBars();
}

void SelectorWidget::scrollContentsBy(int dx, int dy)
{
	cartesians_.SetXOffset(QAbstractScrollArea::horizontalScrollBar()->value());
	cartesians_.SetYOffset(QAbstractScrollArea::verticalScrollBar()->value());

	// Notify behaviour object on scroll
	AreasSelector::IBehaviourPtr behaviour = WidgetImpl::GetBehaviour();
	if ( behaviour )
	{
		behaviour->OnScroll(dx, dy);	
	}

	// Update viewport
	viewport()->update();
}

void SelectorWidget::mouseMoveEvent(QMouseEvent* event)
{
	AreasSelector::IBehaviourPtr behaviour = WidgetImpl::GetBehaviour();
	if ( behaviour )
	{
		behaviour->OnMouseMove(
			cartesians_.InverseX(event->x()), cartesians_.InverseY(event->y()), event->modifiers());
	}

	// Update viewport
	viewport()->update();
}

void SelectorWidget::mousePressEvent(QMouseEvent* event)
{
	AreasSelector::IBehaviourPtr behaviour = WidgetImpl::GetBehaviour();
	if ( behaviour )
	{
		behaviour->OnMousePress(
			cartesians_.InverseX(event->x()), cartesians_.InverseY(event->y()), event->modifiers());
	}

	// Update viewport
	viewport()->update();
}

void SelectorWidget::mouseReleaseEvent(QMouseEvent* event)
{
	AreasSelector::IBehaviourPtr behaviour = WidgetImpl::GetBehaviour();
	if ( behaviour )
	{
		behaviour->OnMouseRelease(
			cartesians_.InverseX(event->x()), cartesians_.InverseY(event->y()), event->modifiers());
	}	

	// Update viewport
	viewport()->update();
}

void SelectorWidget::contextMenuEvent(QContextMenuEvent* event)
{
	AreasSelector::IBehaviourPtr behaviour = WidgetImpl::GetBehaviour();
	if ( behaviour )
	{
		behaviour->OnContextMenu(
			cartesians_.InverseX(event->pos().x()), cartesians_.InverseY(event->pos().y()),
			event->globalPos().x(), event->globalPos().y());
	}

	// Update viewport
	viewport()->update();
}

void SelectorWidget::wheelEvent(QWheelEvent* event)
{
	float ratio = ( event->delta() > 0 ) ? ( 2.0f ) : ( 0.5f );
	if ( !cartesians_.Zoom(ratio, event->pos().x(), event->pos().y()) )
		return;

	ConfigureScrollBars();
	UpdateScrollBars();

	AreasSelector::IBehaviourPtr behaviour = WidgetImpl::GetBehaviour();
	if ( behaviour )
	{
		/* behaviour->OnMouseWheel(
			!!! AdjustX(event->pos().x()), AdjustY(event->pos().y()),
			event->delta(), 
			( event->orientation() == Qt::Horizontal )); */
	}

	// Update viewport
	viewport()->update();
}

// Gui tools
void SelectorWidget::UpdateScrollBars()
{
	int yOffsetBackup = cartesians_.GetYOffset();		
	QAbstractScrollArea::horizontalScrollBar()->setValue(cartesians_.GetXOffset());
	cartesians_.SetYOffset(yOffsetBackup);
	QAbstractScrollArea::verticalScrollBar()->setValue(cartesians_.GetYOffset());
}

void SelectorWidget::ConfigureScrollBars()
{
	if ( !pImage_ )
	{
		// Update viewport settings
		cartesians_.Reset();
		cartesians_.SetData(0, 0);

		// Configure scroll bars
		ConfigureScrollBar(QAbstractScrollArea::horizontalScrollBar(), 0, 0);
		ConfigureScrollBar(QAbstractScrollArea::verticalScrollBar(), 0, 0);

		return;
	}

	cartesians_.SetData(pImage_->width(), pImage_->height());

	cartesians_.BackupOffset();

	ConfigureScrollBar(QAbstractScrollArea::horizontalScrollBar(), 
		cartesians_.GetHorizMax(), cartesians_.GetHorizStep());
	ConfigureScrollBar(QAbstractScrollArea::verticalScrollBar(), 
		cartesians_.GetVertMax(), cartesians_.GetVertStep());

	cartesians_.RestoreOffset();
}

void SelectorWidget::ConfigureScrollBar(QScrollBar* pBar, int maximum, int pageStep)
{
	if ( !pBar )
		return;

	pBar->setMinimum(0);
	pBar->setMaximum(maximum);
	pBar->setPageStep(pageStep);
}