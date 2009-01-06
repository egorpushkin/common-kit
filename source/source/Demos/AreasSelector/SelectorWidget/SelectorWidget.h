#ifndef SELECTORWIDGET_H
#define SELECTORWIDGET_H

#include <QWidget>
#include <QtGui>

#include "Common/Common.h"

#include "Geometry/Cartesians.h"

class SelectorWidget 
	: public QAbstractScrollArea
	, public mc::CommonImpl< Selector::ISelectorControl >
	, public mc::APImpl
	, public mc::AgentImpl
	, public Selector::WidgetImpl
{
	Q_OBJECT

public:
		
	SelectorWidget(QWidget *parent = 0);
	~SelectorWidget();

	// ICommon section
	DECLARE_INTERFACE_MAP()

	// ISelectorControl section
	virtual mc::result SetProject(Areas::IAProjectRef project);

	virtual Areas::IAProjectPtr GetProject();

	// IAgent section
	virtual mc::result Invoke(mc::DispId idMember, mc::DispParamsRef dispParams, mc::IVariantWrapperRef result);

private:

	// Handlers
	void UpdateImage();

	// Event dispatchers
	mc::result OnProjectChanged();

protected:

	// Gui handlers
	virtual void paintEvent(QPaintEvent* event);

	virtual void resizeEvent(QResizeEvent* event);

	virtual void scrollContentsBy(int dx, int dy); 

	virtual void mouseMoveEvent(QMouseEvent* event);

	virtual void mousePressEvent(QMouseEvent* event); 

	virtual void mouseReleaseEvent(QMouseEvent* event); 

	virtual void contextMenuEvent(QContextMenuEvent* event);

	virtual void wheelEvent(QWheelEvent* event);

private:
	
	// Gui tools
	void UpdateScrollBars();

	void ConfigureScrollBars();

	void ConfigureScrollBar(QScrollBar* pBar, int maximum, int pageStep);

private:

	Areas::IAProjectPtr project_;

	QImage* pImage_;

	Geometry::Cartesians cartesians_;

};

#endif // !SELECTORWIDGET_H