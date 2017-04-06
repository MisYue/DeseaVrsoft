#include "testouterlib.h"
#include <QtWidgets/QApplication>
#include <BITUnitsSupport/Bit_USTransform.h>
#ifdef _DEBUG
#pragma comment(lib, "BITUnitsSupportd.lib")

#else
#pragma comment(lib, "BITUnitsSupportr.lib")
#endif

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	Bit_USTransform ust;
	Bit_UnitSystem us(3, 2, 3);
	Bit_UnitSystem us2(1, 2, 3);
	double density = ust.TransformValue(us, us2, 1820, Density);

	TestOuterLib w;
	w.show();
	return a.exec();
}
