#ifndef AREASSELECTOR_H
#define AREASSELECTOR_H

#include <QtGui/QDialog>
#include "ui_areasselector.h"

#include "Common/Common.h"

class AreasSelector : public QDialog
{
	
	Q_OBJECT

public:
	
	AreasSelector(QWidget *parent = 0, Qt::WFlags flags = 0);
	~AreasSelector();


private:

	mc::result ConfigureProject();

private:
	
	Ui::AreasSelectorClass ui;

	mc::ICommonPtr selectorCommon_;
	
	mc::ICommonPtr selectorMirrorCommon_;

	Areas::IAProjectPtr project_;

};

#endif // AREASSELECTOR_H
