#include "DefaultBehaviour.h"

#include "Serialization/AsciiAreas.h"

#include "SelectorProperties.h"

#include "SelectorPainter.h"

namespace Selector
{

	DefaultBehaviour::DefaultBehaviour()
		: QWidget()
		, mc::CommonImpl< IBehaviour >()
		, mc::ItemImpl()
		, mc::AgentImpl()
		, properties_(new Properties)
		, state_(STATE_FREE)
		, selection_()
		, contextPoint_()
		, contextPosition_()
		, startPosition_()
		, currentPosition_()
	{
		CreateActions();
	}

	DefaultBehaviour::~DefaultBehaviour()
	{
	}

	// ICommon section
	BEGIN_INTERFACE_MAP(DefaultBehaviour)
		COMMON(Selector::IBehaviour)
		INTERFACE_(Selector::IBehaviour, Selector::IID_IBehaviour)
		IMPL(mc::ItemImpl)
		IMPL(mc::AgentImpl)
	END_INTERFACE_MAP()

	// IBehaviour section
	mc::result DefaultBehaviour::OnPaint(QPainter& painter)
	{
		ISelectorControlPtr selectorCtrl(mc::ItemImpl::GetParent(), IID_ISelectorControl); 
		if ( !selectorCtrl )
			return mc::_E_FAIL;

		return SelectorPainter::DrawProject(painter, selectorCtrl->GetProject(), *this);
	}

	mc::result DefaultBehaviour::OnResize(int width, int height)
	{
		return mc::_E_NOTIMPL;
	}

	mc::result DefaultBehaviour::OnScroll(int dx, int dy)
	{
		return mc::_E_NOTIMPL;
	}

	mc::result DefaultBehaviour::OnMouseMove(int x, int y, unsigned long modifyers)
	{
		switch ( state_ )
		{
		case STATE_DRAGGING:
		{
			PointsSetCIter_ iter = selection_.begin();
			PointsSetCIter_ end = selection_.end();

			for ( ; iter != end ; ++iter )
			{
				(*iter)->SetLocation(x, y);
			}
		}
		break;
		case STATE_SELECTING:
		{			
		}
		break;
		}

		currentPosition_ = QPoint(x, y);

		return mc::_S_OK;
	}

	mc::result DefaultBehaviour::OnMousePress(int x, int y, unsigned long modifyers)
	{
		Areas::IPointPtr point = GetPointByPosition(x, y);
		if ( point )
		{
			// Initiate dragging
			state_ = STATE_DRAGGING;

			selection_.clear();

			selection_.insert(point);
		}
		else
		{
			// Initiate selecting
			state_ = STATE_SELECTING;

			selection_.clear();
		}

		startPosition_ = QPoint(x, y);

		return mc::_S_OK;
	} 

	mc::result DefaultBehaviour::OnMouseRelease(int x, int y, unsigned long modifyers)
	{
		state_ = STATE_FREE;

		return mc::_S_OK;
	} 

	mc::result DefaultBehaviour::OnContextMenu(int x, int y, int globalX, int globalY)
	{
		contextPoint_ = GetPointByPosition(x, y);		
		contextPosition_ = QPoint(x, y);

		if ( contextPoint_ )
		{
			// Show point's context menu
			QMenu menu(this);
			menu.addAction(newPointAct_);
			menu.addAction(deletePointAct_);
			menu.exec(QPoint(globalX, globalY));
		}
		else
		{
			// Show global menu
			QMenu menu(this);
			menu.addAction(newAreaAct_);
			menu.addSeparator();
			menu.addAction(loadImageAct_);
			menu.addAction(saveProjectAct_);
			menu.addSeparator();
			menu.addAction(propertiesAct_);
			menu.exec(QPoint(globalX, globalY));
		}

		return mc::_S_OK;
	}

	mc::result DefaultBehaviour::OnMouseWheel(int x, int y, int delta, bool horiz)
	{
		return mc::_E_NOTIMPL;
	}

	// IAgent section
	mc::result DefaultBehaviour::Invoke(mc::DispId idMember, mc::DispParamsRef dispParams, mc::IVariantWrapperRef result)
	{
		if ( idMember == AGENTID_PROJECTCHANGED )
		{
			ResetState();
		}

		return mc::_S_OK;
	}

	// Private tools
	void DefaultBehaviour::ResetState()
	{
		state_ = STATE_FREE;
		


	}

	Areas::IPointPtr DefaultBehaviour::GetPointByPosition(int x, int y)
	{
		ISelectorControlPtr selectorCtrl(mc::ItemImpl::GetParent(), IID_ISelectorControl); 
		if ( !selectorCtrl )
			return NULL;

		Project::IContainerPtr areasCotainer(selectorCtrl->GetProject(), Project::IID_IContainer);
		if ( !areasCotainer )
			return NULL;

		double minimalDistance = 9.0f * 9.0f;
		Areas::IPointPtr nearestPoint;

		Container::ICommonEnumPtr cmnAreas = areasCotainer->GetItems();
		for ( bool hasArea = cmnAreas->SelectFirst() ; hasArea ; hasArea = cmnAreas->SelectNext() )
		{
			Project::IContainerPtr pointsCotainer(cmnAreas->GetSelected(), Project::IID_IContainer);
			if ( !pointsCotainer )
				continue;

			Container::ICommonEnumPtr cmnPoints = pointsCotainer->GetItems();
			for ( bool hasPoint = cmnPoints->SelectFirst() ; hasPoint ; hasPoint = cmnPoints->SelectNext() )
			{
				Areas::IPointPtr point(cmnPoints->GetSelected(), Areas::IID_IPoint);
				if ( !point )
					continue;

				const double currentDistance = ( (point->GetX() - x)*(point->GetX() - x) + 
					(point->GetY() - y)*(point->GetY() - y) );
				if ( currentDistance < minimalDistance )
				{
					minimalDistance = currentDistance;
					nearestPoint = point;
				}
			}
		}	

		return nearestPoint;
	}

	// Gui tools
	void DefaultBehaviour::CreateActions()
	{
		// Global actions
		newAreaAct_ = new QAction(tr("&New Area"), this);
		newAreaAct_->setStatusTip(tr("Create a new area"));
		connect(newAreaAct_, SIGNAL(triggered()), this, SLOT(newArea()));

		loadImageAct_ = new QAction(tr("Load Image"), this);
		loadImageAct_->setStatusTip(tr("Load background image"));
		connect(loadImageAct_, SIGNAL(triggered()), this, SLOT(loadImage()));

		saveProjectAct_ = new QAction(tr("Save Project"), this);
		saveProjectAct_->setStatusTip(tr("Save project"));
		connect(saveProjectAct_, SIGNAL(triggered()), this, SLOT(saveProject()));

		propertiesAct_ = new QAction(tr("Properties..."), this);
		propertiesAct_->setStatusTip(tr("Selector display properties"));
		connect(propertiesAct_, SIGNAL(triggered()), this, SLOT(showProperties()));

		// Point actions
		newPointAct_ = new QAction(tr("&New Point"), this);
		newPointAct_->setStatusTip(tr("Create a new point"));
		connect(newPointAct_, SIGNAL(triggered()), this, SLOT(newPoint()));

		deletePointAct_ = new QAction(tr("&Delete Point"), this);
		deletePointAct_->setStatusTip(tr("Delete point"));
		connect(deletePointAct_, SIGNAL(triggered()), this, SLOT(deletePoint()));

	}

	// Gui slots
	void DefaultBehaviour::newArea()
	{
		// Acquire selector control
		ISelectorControlPtr selectorCtrl(mc::ItemImpl::GetParent(), IID_ISelectorControl); 
		if ( !selectorCtrl )
			return;

		// Acquire porject
		Areas::IAProjectPtr project = selectorCtrl->GetProject();
		if ( !project )
			return;

		// Instantiate new area
		mc::ICommonPtr cmnArea = Components::InstantiateCommon(Areas::LIBID_Areas, Areas::CLSID_Area); 
		Project::IContainerPtr pointsContainer(cmnArea, Project::IID_IContainer);

		// Add point
		mc::ICommonPtr cmnPoint = Components::InstantiateCommon(Areas::LIBID_Areas, Areas::CLSID_Point); 
		Areas::IPointPtr point = Areas::IPointPtr(cmnPoint, Areas::IID_IPoint);
		point->SetLocation(contextPosition_.x(), contextPosition_.y() - 15);
		pointsContainer->Add(cmnPoint);		

		// Add point
		cmnPoint = Components::InstantiateCommon(Areas::LIBID_Areas, Areas::CLSID_Point); 
		point = Areas::IPointPtr(cmnPoint, Areas::IID_IPoint);
		point->SetLocation(contextPosition_.x() - 15, contextPosition_.y() + 15);
		pointsContainer->Add(cmnPoint);		

		// Add point
		cmnPoint = Components::InstantiateCommon(Areas::LIBID_Areas, Areas::CLSID_Point); 
		point = Areas::IPointPtr(cmnPoint, Areas::IID_IPoint);
		point->SetLocation(contextPosition_.x() + 15, contextPosition_.y() + 15);
		pointsContainer->Add(cmnPoint);		

		// Add configured area to project
		Project::IContainerPtr areasContainer(project, Project::IID_IContainer);
		areasContainer->Add(cmnArea);
	}

	void DefaultBehaviour::loadImage()
	{
		ISelectorControlPtr selectorCtrl(mc::ItemImpl::GetParent(), IID_ISelectorControl); 
		if ( !selectorCtrl )
			return;

		Areas::IAProjectPtr project = selectorCtrl->GetProject();
		if ( !project )
			return;

		QString fileName = 
			QFileDialog::getOpenFileName(this,
			tr("Load Background Image"), QString(), tr("PGM Image File (*.pgm)"), NULL,
			QFileDialog::DontUseNativeDialog); 
		if ( fileName == QString() )
			return;

		Areas::IMsImagePtr image = project->GetImage();

		image->SetSrcName(fileName.toAscii().data());
	}

	void DefaultBehaviour::saveProject()
	{
		ISelectorControlPtr selectorCtrl(mc::ItemImpl::GetParent(), IID_ISelectorControl); 
		if ( !selectorCtrl )
			return;

		Areas::IAProjectPtr project = selectorCtrl->GetProject();
		if ( !project )
			return;

		QString fileName = 
			QFileDialog::getSaveFileName(this,
			tr("Save Project"), QString(), tr("Ascii Project File (*.dat)"), NULL,
			QFileDialog::DontUseNativeDialog); 
		if ( fileName == QString() )
			return;

		Serialization::AsciiAreas areasLoader;
		areasLoader.SaveProject(fileName.toAscii().data(), project);
	}

	void DefaultBehaviour::showProperties()
	{
		SelectorProperties props(this, properties_);
		props.exec();
	}

	void DefaultBehaviour::newPoint()
	{
		if ( contextPoint_ )
		{
			// Query for item interface
			mc::IItemPtr pointItem(contextPoint_, mc::IID_IItem);
			if ( !pointItem )
				return;
			
			// Get point's parent item
			Project::IContainerPtr pointsContainer(
				pointItem->GetParent(), Project::IID_IContainer);
			if ( !pointsContainer )
				return;

			// Instantiate new point 
			mc::ICommonPtr cmnPoint = Components::InstantiateCommon(Areas::LIBID_Areas, Areas::CLSID_Point); 
			Areas::IPointPtr point = Areas::IPointPtr(cmnPoint, Areas::IID_IPoint);

			// Specify it's location
			point->SetLocation(
				contextPoint_->GetX() + 10, contextPoint_->GetY() + 10);

			// Add constructed and configured point
			pointsContainer->InsertAfter(cmnPoint, contextPoint_);	
		}		
	}

	void DefaultBehaviour::deletePoint()
	{
		if ( contextPoint_ )
		{
			// Query for item interface
			mc::IItemPtr pointItem(contextPoint_, mc::IID_IItem);
			if ( !pointItem )
				return;

			// Get point's parent item
			Project::IContainerPtr pointsContainer(pointItem->GetParent(), Project::IID_IContainer);
			if ( !pointsContainer )
				return;

			if ( pointsContainer->GetItems()->GetTotal() <= 3 )
			{
				int ret = QMessageBox::question(this, 
					tr("Areas Selector control"),
					tr("Area cannot contain less than 3 points.\n"
					"Do you want to delete the whole area?"),
					QMessageBox::Yes | QMessageBox::No,
					QMessageBox::Yes); 
				if ( ret == QMessageBox::Yes )
				{
					// Query for item interface
					mc::IItemPtr areaItem(pointsContainer, mc::IID_IItem);
					if ( !areaItem )
						return;

					// Get areas's parent item
					Project::IContainerPtr areasContainer(areaItem->GetParent(), Project::IID_IContainer);
					if ( !areasContainer ) 
						return;

					areasContainer->Delete(mc::ICommonPtr(areaItem, mc::IID_ICommon));
				}
			}
			else
			{
				// Area contains a loot of points and one of them can be removed

				// Delete point 
				pointsContainer->Delete(contextPoint_);		

				// Update context state
				contextPoint_ = NULL;

				// TODO: Delete point from the list of selected items
			}
		}	
	}

}