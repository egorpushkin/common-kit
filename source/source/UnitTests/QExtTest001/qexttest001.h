#ifndef QEXTTEST001_H
#define QEXTTEST001_H

#include <QtGui/QMainWindow>
#include "ui_qexttest001.h"

#include "AreasKit/AreasKit.h"

class QExtTest001 : public QMainWindow
{
	Q_OBJECT

public:
	QExtTest001(QWidget *parent = 0, Qt::WFlags flags = 0);
	~QExtTest001();

private:

	Ui::QExtTest001Class ui;

	Areas::IAProjectPtr project_;

};

#endif // QEXTTEST001_H
