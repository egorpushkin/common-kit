#ifndef AREANAME_H
#define AREANAME_H

#include <QDialog>
#include "ui_AreaName.h"

class AreaName : public QDialog
{
	Q_OBJECT

public:
	AreaName(const QString& name, QWidget *parent = 0);
	~AreaName();

	QString GetName();
	
private:
	
	Ui::AreaNameClass ui;

private slots:

	void on_ok__clicked();

};

#endif // AREANAME_H
