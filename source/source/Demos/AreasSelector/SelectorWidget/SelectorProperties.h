#ifndef SELECTORPROPERTIES_H
#define SELECTORPROPERTIES_H

#include <QDialog>
#include "ui_SelectorProperties.h"

#include "Common/Common.h"

#include "Properties.h"

class SelectorProperties : public QDialog
{
	Q_OBJECT

public:

	SelectorProperties(QWidget *parent = 0, Selector::PropertiesRef properties_ = NULL);	

	~SelectorProperties();

private:

	void SetColor(QWidget* pWidget, const QColor& color);

private:

	Ui::SelectorProperties ui;

	Selector::PropertiesPtr properties_;


private slots:

	void on_connectorColor__clicked();
	void on_connectorWidth__textChanged(const QString&);
	void on_displayConnectors__clicked(bool);
	void on_displayLabels__clicked(bool);
	void on_labelColor__clicked();
	void on_labelFont__currentFontChanged(const QFont&);
	void on_labelSize__textChanged(const QString&);
	void on_labelYOffset__textChanged(const QString&);
	void on_labelXOffset__textChanged(const QString&);
	void on_radius__textChanged(const QString&);
	void on_selectFreeColor__clicked();
	void on_displayPoints__clicked(bool);
	void on_selectSelectedColor__clicked();

};

#endif // SELECTORPROPERTIES_H
