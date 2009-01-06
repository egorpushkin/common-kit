#ifndef QMCWIDGET_H
#define QMCWIDGET_H

#include <QWidget>
#include <QGridLayout>
#include <QtDesigner/QDesignerExportWidget>

#ifdef QDESIGNER_EXPORT_WIDGETS
#define WIDGET_EXPORT_SIGNATURE QDESIGNER_WIDGET_EXPORT
#else
#define WIDGET_EXPORT_SIGNATURE
#define WIDGET_CONTROL
#endif

#ifdef WIDGET_CONTROL

#include "QKit/QKit.h"

#endif // WIDGET_CONTROL

class WIDGET_EXPORT_SIGNATURE QMcWidget 
	: public QWidget
{	
	Q_OBJECT

public:
	
	QMcWidget(QWidget* parent = 0);
	~QMcWidget();

#ifdef WIDGET_CONTROL	

	mc::result Attach(mc::RefClsid objId);

	mc::result Attach(mc::RefIid libIid, mc::RefClsid objId);

	mc::ICommonPtr GetCommon();

#endif // WIDGET_CONTROL

private:

#ifdef WIDGET_CONTROL	
	
	mc::result AttachCore();

#endif // WIDGET_CONTROL

private:

#ifdef WIDGET_CONTROL	

	QGridLayout* gridLayout_;

	mc::ICommonPtr attachedControl_;

#endif // WIDGET_CONTROL

protected:

#ifndef WIDGET_CONTROL	

	void paintEvent(QPaintEvent* event);

#endif // !WIDGET_CONTROL

};

#endif // QMCWIDGET_H
