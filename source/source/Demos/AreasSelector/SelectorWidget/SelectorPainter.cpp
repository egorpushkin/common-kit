#include "Spirits/DefaultBehaviour.h"

#include "SelectorPainter.h"

namespace Selector
{

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

		// Enumerate points
		PointsList_ points;

		Container::ICommonEnumPtr cmnPoints = pointsCotainer->GetItems();
		for ( bool hasPoint = cmnPoints->SelectFirst() ; hasPoint ; hasPoint = cmnPoints->SelectNext() )
		{
			mc::ICommonPtr cmnPoint = cmnPoints->GetSelected();

			Areas::IPointPtr point(cmnPoint, Areas::IID_IPoint);

			points.push_back(point);
		}

		if ( behaviour.properties_->displayConnections_ )
		{
			// Draw connections via internal tool
			DrawConnections(painter, points, behaviour);
		}

		if ( behaviour.properties_->displayPoints_ )
		{
			// Draw points via internal tool
			DrawPoints(painter, points, behaviour);
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

			QRect v = painter.viewport();
			QRect w = painter.window();

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

}
