#include "Spirits/DefaultBehaviour.h"

#include "SelectorWidget.h"

#include "SelectorPainter.h"

namespace AreasSelector
{

	mc::result SelectorPainter::ConfigurePainter(QPainter& painter)
	{
		// Configure painter
		painter.setRenderHint(QPainter::Antialiasing);

		return mc::_S_OK;
	}

	mc::result SelectorPainter::DrawBackground(QPainter& painter, const SelectorWidget& widget)
	{
		int toolX, toolY, toolWidth, toolHeight;

		// Configure viewport and scaling
		widget.cartesians_.ConfigurePainterWindow(toolX, toolY, toolWidth, toolHeight);
		QRect painterWindowRect(toolX, toolY, toolWidth, toolHeight);

		painter.setWindow(painterWindowRect);
		painter.scale(widget.cartesians_.GetScale(), widget.cartesians_.GetScale());

		// Draw background
		if ( widget.pImage_ )
		{
			widget.cartesians_.ConfigureSource(toolX, toolY, toolWidth, toolHeight);
			QRect source(toolX, toolY, toolWidth, toolHeight);

			widget.cartesians_.ConfigureTarget(toolX, toolY, toolWidth, toolHeight);
			QRect target(toolX, toolY, toolWidth, toolHeight);

			painter.drawImage(target, *widget.pImage_, source);
		}		

		return mc::_S_OK;
	}

	mc::result SelectorPainter::DrawProject(QPainter& painter, Areas::IAProjectRef project, const DefaultBehaviour& behaviour)
	{
		if ( !project )
			return mc::_E_INVALIDARG;

		Project::IContainerPtr areasCotainer(project, Project::IID_IContainer);
		if ( !areasCotainer )
			return mc::_E_INVALIDARG;

		Container::ICommonEnumPtr cmnAreas = areasCotainer->GetItems();
		for ( bool hasArea = cmnAreas->SelectFirst() ; hasArea ; hasArea = cmnAreas->SelectNext() )
		{
			DrawArea(painter, cmnAreas->GetSelected(), behaviour);
		}	

		return mc::_S_OK;
	}

	mc::result SelectorPainter::DrawArea(QPainter& painter, mc::ICommonPtr cmnArea, const DefaultBehaviour& behaviour)
	{
		// Check input arguments
		if ( !cmnArea )
			return mc::_E_INVALIDARG;

		// Query points container
		Project::IContainerPtr pointsCotainer(cmnArea, Project::IID_IContainer);
		if ( !pointsCotainer )
			return mc::_E_INVALIDARG;

		// Label position
		double labelPosX = 0.0f;
		double labelPosY = 0.0f;

		// Enumerate points
		PointsList_ points;

		Container::ICommonEnumPtr cmnPoints = pointsCotainer->GetItems();
		for ( bool hasPoint = cmnPoints->SelectFirst() ; hasPoint ; hasPoint = cmnPoints->SelectNext() )
		{
			mc::ICommonPtr cmnPoint = cmnPoints->GetSelected();

			Areas::IPointPtr point(cmnPoint, Areas::IID_IPoint);

			points.push_back(point);

			labelPosX += point->GetX();
			labelPosY += point->GetY();
		}

		labelPosX /= cmnPoints->GetTotal();
		labelPosY /= cmnPoints->GetTotal();

		if ( behaviour.properties_->displayConnections_ )
		{
			// Draw connections via internal tool
			DrawConnections(painter, points, behaviour);
		}

		if ( behaviour.properties_->displayPoints_ || behaviour.properties_->displayLabels_ )
		{
			// Draw points via internal tool
			DrawPoints(painter, points, behaviour);
		}

		if ( true )
		{
			// Draw label
			DrawLabel(painter, cmnArea, labelPosX, labelPosY, behaviour);
		}

		return mc::_S_OK;
	}

	mc::result SelectorPainter::DrawConnections(QPainter& painter, const PointsList_& points, const DefaultBehaviour& behaviour)
	{
		QPen connPen(QBrush(behaviour.properties_->connectionColor_), behaviour.properties_->connectionWidth_, Qt::SolidLine, Qt::RoundCap);
		painter.setPen(connPen);

		double prevX = -1;
		double prevY = -1;

		PointsListCIter_ iter = points.begin();
		PointsListCIter_ end = points.end();

		if ( iter == end )
			return mc::_S_FALSE;

		double firstX = (*iter)->GetX();
		double firstY = (*iter)->GetY();

		for ( int i = 0 ; iter != end ; ++iter, ++i )
		{
			Areas::IPointPtr point = (*iter);

			double curX = point->GetX();
			double curY = point->GetY();

			if ( prevX != -1 )
			{
				painter.drawLine((int)prevX, (int)prevY, (int)curX, (int)curY);
			}

			prevX = curX;
			prevY = curY;
		}

		painter.drawLine((int)prevX, (int)prevY, (int)firstX, (int)firstY);

		return mc::_S_OK;
	}

	mc::result SelectorPainter::DrawPoints(QPainter& painter, const PointsList_& points, const DefaultBehaviour& behaviour)
	{
		QPen pointPen(QBrush(QColor()), behaviour.properties_->radius_, Qt::SolidLine, Qt::RoundCap);

		if ( behaviour.properties_->displayLabels_ )
			painter.setFont(behaviour.properties_->labelFont_);

		// Draw points over lines
		PointsListCIter_ iter = points.begin();
		PointsListCIter_ end = points.end();

		for ( int i = 0 ; iter != end ; ++iter, ++i )
		{
			Areas::IPointPtr point = (*iter);

			//QRect v = painter.viewport();
			//QRect w = painter.window();

			if ( behaviour.properties_->displayPoints_ )
			{
				if ( behaviour.selection_.find(point) != behaviour.selection_.end() )
				{
					// Selected
					pointPen.setColor(behaviour.properties_->selectedColor_);
					painter.setPen(pointPen);
				}
				else
				{
					// Free
					pointPen.setColor(behaviour.properties_->freeColor_);				
				}

				painter.setPen(pointPen);
				painter.drawPoint(point->GetX(), point->GetY());
			}

			if ( behaviour.properties_->displayLabels_ )
			{
				painter.setPen(behaviour.properties_->labelColor_);

				painter.drawText(
					point->GetX() + behaviour.properties_->labelXOffset_, 
					point->GetY() + behaviour.properties_->labelYOffset_,
					QString::number(i));
			}
		}

		return mc::_S_OK;
	}

	mc::result SelectorPainter::DrawLabel(QPainter& painter, mc::ICommonPtr cmnArea, double x, double y, const DefaultBehaviour& behaviour)
	{
		Areas::IAreaPtr area(cmnArea, Areas::IID_IArea); 
		if ( !area )
			return mc::_E_FAIL;

		painter.setFont(behaviour.properties_->labelFont_);
		painter.setPen(behaviour.properties_->labelColor_);

		painter.drawText(
			x - 20 + behaviour.properties_->labelXOffset_, 
			y + behaviour.properties_->labelYOffset_,
			area->GetName().c_str());

		return mc::_S_OK;
	}

}
