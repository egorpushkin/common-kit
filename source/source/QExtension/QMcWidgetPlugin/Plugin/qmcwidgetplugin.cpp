#include <QtCore/QtPlugin>

#include "qmcwidgetplugin.h"
#include "Widget/qmcwidget.h"

QMcWidgetPlugin::QMcWidgetPlugin(QObject *parent)
	: QObject(parent)
{
	initialized = false;
}

void QMcWidgetPlugin::initialize(QDesignerFormEditorInterface * /*core*/)
{
	if (initialized)
		return;

	initialized = true;
}

bool QMcWidgetPlugin::isInitialized() const
{
	return initialized;
}

QWidget *QMcWidgetPlugin::createWidget(QWidget *parent)
{
	return new QMcWidget(parent);
}

QString QMcWidgetPlugin::name() const
{
	return "QMcWidget";
}

QString QMcWidgetPlugin::group() const
{
	return "Display Widgets [Examples]";
}

QIcon QMcWidgetPlugin::icon() const
{
	return QIcon();
}

QString QMcWidgetPlugin::toolTip() const
{
	return QString();
}

QString QMcWidgetPlugin::whatsThis() const
{
	return QString();
}

bool QMcWidgetPlugin::isContainer() const
{
	return false;
}

QString QMcWidgetPlugin::domXml() const
{
	return "<widget class=\"QMcWidget\" name=\"qMcWidget\">\n"
		" <property name=\"geometry\">\n"
		"  <rect>\n"
		"   <x>0</x>\n"
		"   <y>0</y>\n"
		"   <width>100</width>\n"
		"   <height>100</height>\n"
		"  </rect>\n"
		" </property>\n"
		"</widget>\n";
}

QString QMcWidgetPlugin::includeFile() const
{
	return "qmcwidget.h";
}

Q_EXPORT_PLUGIN2(qmcwidgetplugin, QMcWidgetPlugin)
