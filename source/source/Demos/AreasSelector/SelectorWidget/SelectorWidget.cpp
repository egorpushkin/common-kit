#include <QtGui>

#include "SelectorWidget.h"

#include "Spirits/DefaultBehaviour.h"

SelectorWidget::SelectorWidget(QWidget* parent)
	: QAbstractScrollArea(parent)
	, mc::CommonImpl< Selector::ISelectorControl >()
	, mc::APImpl()
	, mc::AgentImpl()
	, WidgetImpl()
	, project_()
	, pImage_(NULL)
	, cartesians_()
{
	mc::CommonImpl< Selector::ISelectorControl >::AddRef();

	WidgetImpl::SetBehaviour(
		Selector::IBehaviourPtr(
			mc::ObjectCreator< Selector::DefaultBehaviour >(), 
			Selector::IID_IBehaviour));
}

SelectorWidget::~SelectorWidget()
{
	delete pImage_;
}

// ICommon section
BEGIN_INTERFACE_MAP(SelectorWidget)
	COMMON(Selector::ISelectorControl)
	INTERFACE_(Selector::ISelectorControl, Selector::IID_ISelectorControl)
	IMPL(mc::APImpl)
	IMPL(mc::AgentImpl)
	IMPL(Selector::WidgetImpl)
END_INTERFACE_MAP()

// ISelectorWidget section
mc::result SelectorWidget::SetProject(Areas::IAProjectRef project)
{
	if ( project_ )
	{
		// Unadvise sink from project
		// Restore project's parent
	}

	project_ = project;

	UpdateImage();

	mc::ICommonPtr local = mc::APImpl::GetLocal();

	if ( project_ )
	{
		// Set parent item for project
		mc::IItemPtr projectItem(project_, mc::IID_IItem);
		if ( projectItem )
			projectItem->SetParent(local);

		// Subscribe on project's events
		unsigned long cookie = 0;
		mc::Advise(mc::ICommonPtr(project_, mc::IID_ICommon), local, cookie);
	}

	// Configure behaviour
	mc::IItemPtr behaviourItem(Selector::WidgetImpl::GetBehaviour(), mc::IID_IItem);
	if ( behaviourItem )
	{
		behaviourItem->SetParent(local);
	}

	// Notify all sinks on new project
	OnProjectChanged();

	viewport()->update();

	return mc::_S_OK;
}

Areas::IAProjectPtr SelectorWidget::GetProject()
{
	return project_;
}

// IAgent section
mc::result SelectorWidget::Invoke(mc::DispId idMember, mc::DispParamsRef dispParams, mc::IVariantWrapperRef result)
{
	if ( idMember == Areas::AGENTID_IMGCHANGED )
	{
		UpdateImage();
		viewport()->update();
	}
	
	switch ( idMember )
	{
	case Areas::AGENTID_AREAADDED:
	case Areas::AGENTID_AREADELETED:
	case Areas::AGENTID_POINTADDED:
	case Areas::AGENTID_POINTDELETED:
	case Areas::AGENTID_LOCATIONCHANGED:
	{
		viewport()->update();			
	}
	break;
	}

	return mc::_S_OK;
}

// Handlers
void SelectorWidget::UpdateImage()
{
	if ( pImage_ )
	{
		cartesians_.SetData(0, 0);

		delete pImage_;
		pImage_ = NULL;
	}

	if ( !project_ )
		return;

	Areas::IMsImagePtr projectImage = project_->GetImage();
	mc::StringA imgSrcName(projectImage->GetSrcName());

	pImage_ = new QImage(imgSrcName.c_str(), "PGM");
	if ( pImage_->isNull() ) 
	{
		cartesians_.SetData(0, 0);

		delete pImage_;
		pImage_ = NULL;

		return;
	}

	cartesians_.Reset();
	cartesians_.SetData(pImage_->width(), pImage_->height());

	ConfigureScrollBars();
}

// Event dispatchers
mc::result SelectorWidget::OnProjectChanged()
{
	return mc::APImpl::SpreadBase(
		Selector::AGENTID_PROJECTCHANGED, 
		CreateParams(
			mc::ItemImpl::GetLocal()));
}

// Gui handlers
void SelectorWidget::paintEvent(QPaintEvent*)
{
	QPainter painter(viewport());

	int toolX, toolY, toolWidth, toolHeight;

	// Configure painter's rendering 
	painter.setRenderHint(QPainter::Antialiasing);

	// Configure viewport and scaling
	cartesians_.ConfigurePainterWindow(toolX, toolY, toolWidth, toolHeight);
	QRect painterWindowRect(toolX, toolY, toolWidth, toolHeight);

	painter.setWindow(painterWindowRect);
	painter.scale(cartesians_.GetScale(), cartesians_.GetScale());
		
	// Draw background
	if ( pImage_ )
	{
		cartesians_.ConfigureSource(toolX, toolY, toolWidth, toolHeight);
		QRect source(toolX, toolY, toolWidth, toolHeight);

		cartesians_.ConfigureTarget(toolX, toolY, toolWidth, toolHeight);
		QRect target(toolX, toolY, toolWidth, toolHeight);

		painter.drawImage(target, *pImage_, source);
	}

	// Draw content via behaviour
	Selector::IBehaviourPtr behaviour = WidgetImpl::GetBehaviour();
	if ( !behaviour )
		return;

	behaviour->OnPaint(painter);		
}

void SelectorWidget::resizeEvent(QResizeEvent* event)
{
	cartesians_.SetViewport(viewport()->width(), viewport()->height());

	// TODO: Check whether this call works properly here
	ConfigureScrollBars();
}

void SelectorWidget::scrollContentsBy(int dx, int dy)
{
	cartesians_.SetXOffset(QAbstractScrollArea::horizontalScrollBar()->value());
	cartesians_.SetYOffset(QAbstractScrollArea::verticalScrollBar()->value());

	// Notify behaviour object on scroll
	Selector::IBehaviourPtr behaviour = WidgetImpl::GetBehaviour();
	if ( behaviour )
	{
		behaviour->OnScroll(dx, dy);	
	}

	// Update viewport
	viewport()->update();
}

void SelectorWidget::mouseMoveEvent(QMouseEvent* event)
{
	Selector::IBehaviourPtr behaviour = WidgetImpl::GetBehaviour();
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
	Selector::IBehaviourPtr behaviour = WidgetImpl::GetBehaviour();
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
	Selector::IBehaviourPtr behaviour = WidgetImpl::GetBehaviour();
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
	Selector::IBehaviourPtr behaviour = WidgetImpl::GetBehaviour();
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

	Selector::IBehaviourPtr behaviour = WidgetImpl::GetBehaviour();
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
		ConfigureScrollBar(QAbstractScrollArea::horizontalScrollBar(), 0, 0);
		ConfigureScrollBar(QAbstractScrollArea::verticalScrollBar(), 0, 0);

		return;
	}

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