#include "AreaName.h"

AreaName::AreaName(const QString& name, QWidget *parent)
	: QDialog(parent)
{
	ui.setupUi(this);

	ui.areaName_->setText(name);
}

AreaName::~AreaName()
{
}

QString AreaName::GetName()
{
	return ui.areaName_->text();
}

void AreaName::on_ok__clicked()
{
	accept();
}