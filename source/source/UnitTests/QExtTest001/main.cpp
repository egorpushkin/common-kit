#include <QtGui/QApplication>
#include "qexttest001.h"

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	QExtTest001 w;
	w.show();
	a.connect(&a, SIGNAL(lastWindowClosed()), &a, SLOT(quit()));
	return a.exec();
}
