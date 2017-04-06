#include "vrda066.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	VRDA066 w;
	w.show();
	return a.exec();
}
