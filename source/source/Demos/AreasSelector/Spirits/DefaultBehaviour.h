#ifndef DEFAULTBEHAVIOUR_H__AREASSELECTOR__INCLUDED_
#define DEFAULTBEHAVIOUR_H__AREASSELECTOR__INCLUDED_

#include <QtGui>

#include "Common/Common.h"

#include "Properties.h"

namespace Selector
{

	class DefaultBehaviour 
		: QWidget 
		, public mc::CommonImpl< IBehaviour >
		, public mc::ItemImpl
		, public mc::AgentImpl
	{
		Q_OBJECT

		friend class SelectorPainter;

	public:

		DefaultBehaviour();
		virtual ~DefaultBehaviour();

		// ICommon section
		DECLARE_INTERFACE_MAP()

		// IBehaviour section
		virtual mc::result OnPaint(QPainter& painter);

		virtual mc::result OnResize(int width, int height);

		virtual mc::result OnScroll(int dx, int dy);

		virtual mc::result OnMouseMove(int x, int y, unsigned long modifyers);

		virtual mc::result OnMousePress(int x, int y, unsigned long modifyers); 

		virtual mc::result OnMouseRelease(int x, int y, unsigned long modifyers); 

		virtual mc::result OnContextMenu(int x, int y, int globalX, int globalY); 

		virtual mc::result OnMouseWheel(int x, int y, int delta, bool horiz); 

		// IAgent section
		virtual mc::result Invoke(mc::DispId idMember, mc::DispParamsRef dispParams, mc::IVariantWrapperRef result);

	private:

		// Private tools
		void ResetState();

		Areas::IPointPtr GetPointByPosition(int x, int y);

	private:

		// Gui tools
		void CreateActions();

		// Gui data
		QAction* newAreaAct_;

		QAction* loadImageAct_;

		QAction* saveProjectAct_;

		QAction* propertiesAct_;

		QAction* newPointAct_;

		QAction* deletePointAct_;

	private slots:

		// Gui slots
		void newArea();

		void loadImage();

		void saveProject();

		void showProperties();

		void newPoint();

		void deletePoint();

	private:

		typedef enum tagState_
		{

			STATE_FREE = 0x0,

			STATE_DRAGGING,

			STATE_SELECTING

		} State_;

		typedef std::set< Areas::IPointPtr > PointsSet_;

		typedef PointsSet_::const_iterator PointsSetCIter_;

		PropertiesPtr properties_;

		State_ state_;

		PointsSet_ selection_;

		Areas::IPointPtr contextPoint_;

		QPoint contextPosition_;

		QPoint startPosition_;
		
		QPoint currentPosition_;

	};

}

#endif // !DEFAULTBEHAVIOUR_H__AREASSELECTOR__INCLUDED_