#include "SelectorProperties.h"

#include <QColorDialog>

SelectorProperties::SelectorProperties(QWidget *parent, Selector::PropertiesRef properties_)
	: QDialog(parent)
	, ui()
	, properties_(properties_)
{
	ui.setupUi(this);

	// Points
	ui.displayPoints_->setCheckState(( properties_->displayPoints_ ) ? ( Qt::Checked ) : ( Qt::Unchecked ) );
	ui.pointProperties_->setEnabled(properties_->displayPoints_);

	SetColor(ui.selectedColorDisplayer_, properties_->selectedColor_);
	SetColor(ui.freeColorDisplayer_, properties_->freeColor_);
	ui.radius_->setText(QString::number(properties_->radius_));

	// Labels
	ui.displayLabels_->setCheckState(( properties_->displayLabels_ ) ? ( Qt::Checked ) : ( Qt::Unchecked ) );
	ui.labelProperties_->setEnabled(properties_->displayLabels_);

	ui.labelXOffset_->setText(QString::number(properties_->labelXOffset_));
	ui.labelYOffset_->setText(QString::number(properties_->labelYOffset_));
	ui.labelSize_->setText(QString::number(properties_->labelFont_.pointSize()));
	ui.labelFont_->setCurrentFont(properties_->labelFont_);
	SetColor(ui.labelColorDisplayer_, properties_->labelColor_);

	// Connections
	ui.displayConnectors_->setCheckState(( properties_->displayConnections_ ) ? ( Qt::Checked ) : ( Qt::Unchecked ) );
	ui.connectorProperties_->setEnabled(properties_->displayConnections_);

	ui.connectorWidth_->setText(QString::number(properties_->connectionWidth_));
	SetColor(ui.connectorColorDisplayer_, properties_->connectionColor_);

}

SelectorProperties::~SelectorProperties()
{
}

void SelectorProperties::SetColor(QWidget* pWidget, const QColor& color)
{
	QPalette pal;
	pal.setColor(QPalette::Normal, QPalette::Window, color);
	pWidget->setPalette(pal);
}

void SelectorProperties::on_displayPoints__clicked(bool checked)
{
	properties_->displayPoints_ = checked;
}

void SelectorProperties::on_selectSelectedColor__clicked()
{
	QColor newColor = QColorDialog::getColor(properties_->selectedColor_, this);
	if ( newColor.isValid() )
	{
		properties_->selectedColor_ = newColor;
		SetColor(ui.selectedColorDisplayer_, properties_->selectedColor_);
	}
}

void SelectorProperties::on_selectFreeColor__clicked()
{
	QColor newColor = QColorDialog::getColor(properties_->freeColor_, this);
	if ( newColor.isValid() )
	{
		properties_->freeColor_ = newColor;
		SetColor(ui.freeColorDisplayer_, properties_->freeColor_);
	}
}

void SelectorProperties::on_radius__textChanged(const QString& text)
{
	properties_->radius_ = text.toInt();
}

void SelectorProperties::on_labelXOffset__textChanged(const QString& text)
{
	properties_->labelXOffset_ = text.toInt();
}

void SelectorProperties::on_labelYOffset__textChanged(const QString& text)
{
	properties_->labelYOffset_ = text.toInt();
}

void SelectorProperties::on_labelSize__textChanged(const QString& text)
{
	properties_->labelFont_.setPointSize(text.toInt());
}

void SelectorProperties::on_labelFont__currentFontChanged(const QFont& font)
{
	properties_->labelFont_ = font;
	properties_->labelFont_.setBold(true);
	properties_->labelFont_.setPointSize(ui.labelSize_->text().toInt());
}

void SelectorProperties::on_labelColor__clicked()
{
	QColor newColor = QColorDialog::getColor(properties_->labelColor_, this);
	if ( newColor.isValid() )
	{
		properties_->labelColor_ = newColor;
		SetColor(ui.labelColorDisplayer_, properties_->labelColor_);
	}
}

void SelectorProperties::on_displayLabels__clicked(bool checked)
{
	properties_->displayLabels_ = checked;
}


void SelectorProperties::on_displayConnectors__clicked(bool checked)
{
	properties_->displayConnections_ = checked;
}

void SelectorProperties::on_connectorWidth__textChanged(const QString& text)
{
	properties_->connectionWidth_ = text.toInt();
}

void SelectorProperties::on_connectorColor__clicked()
{
	QColor newColor = QColorDialog::getColor(properties_->connectionColor_, this);
	if ( newColor.isValid() )
	{
		properties_->connectionColor_ = newColor;
		SetColor(ui.connectorColorDisplayer_, properties_->connectionColor_);
	}
}