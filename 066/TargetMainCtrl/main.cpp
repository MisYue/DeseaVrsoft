#include "targetmainwnd.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	TargetMainWnd w;
	w.show();
	return a.exec();
}
