#include <WarheadFileReadWrite/warheadfilereadwriteengine.h>
#include <QtCore>

int main(int argc, char *argv[])
{
	QCoreApplication a(argc, argv);
	WarheadFileReadWriteEngine warhead_rw;

	return a.exec();
}
