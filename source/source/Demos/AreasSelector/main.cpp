#include <QtGui/QApplication>
#include "areasselector.h"

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	AreasSelector w;
	w.show();
	a.connect(&a, SIGNAL(lastWindowClosed()), &a, SLOT(quit()));
	return a.exec();
}
