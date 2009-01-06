#ifndef SELECTORPAINTER_H__AREASSELECTOR__INCLUDED_
#define SELECTORPAINTER_H__AREASSELECTOR__INCLUDED_

#include <QtGui>

#include "Common/Common.h"

#include "Properties.h"

namespace Selector
{

	class SelectorPainter
	{
	public:

		static mc::result DrawProject(QPainter& painter, Areas::IAProjectRef project, const DefaultBehaviour& behaviour);

	private:

		typedef std::vector< Areas::IPointPtr > PointsList_;

		typedef PointsList_::const_iterator PointsListCIter_;

	private:

		static mc::result DrawArea(QPainter& painter, mc::ICommonPtr cmnArea, const DefaultBehaviour& behaviour);

		static mc::result DrawConnections(QPainter& painter, const PointsList_& points, const DefaultBehaviour& behaviour);

		static mc::result DrawPoints(QPainter& painter, const PointsList_& points, const DefaultBehaviour& behaviour);



	};

}

#endif // !SELECTORPAINTER_H__AREASSELECTOR__INCLUDED_
