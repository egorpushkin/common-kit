#include <QtGui/QApplication>
#include "UI/areasselector.h"

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	AreasSelectorTool w;

	// Object initialization
	w.Attach(mc::CLSID_This, mc::ICommonPtr(&w, mc::IID_ICommon));
	w.SetLocal(w.Acquire(mc::CLSID_This)); 

	w.show();
	a.connect(&a, SIGNAL(lastWindowClosed()), &a, SLOT(quit()));
	return a.exec();
}
