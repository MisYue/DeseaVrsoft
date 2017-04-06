
#include <QtCore>
#include <BasicTool/CoordConvert2D.h>
#include <BasicTool/EnumMgr.h>
#include <iostream>
#include <typeinfo>

void TestCoordConvert2D()
{
	CoordConvert2D cc2d(M_PI, 50, 0);
	CoordConvert2D cc2d_2(0, 50, 0);

	double x = 20;
	double y = 0;
	cc2d.Convert(x, y);

	//Q_ASSERT(x == 30);
	//Q_ASSERT(y == 0);

	cc2d_2.Convert(x, y);
	//Q_ASSERT(x == -20);
	//Q_ASSERT(y == 0);

	x = 100;
	y = 0;
	cc2d.Convert(x, y);
	//Q_ASSERT(x == -50);
	//Q_ASSERT(y == 0);

	cc2d_2.Convert(x, y);
	//Q_ASSERT(x == -100);
	//Q_ASSERT(y == 0);


	cc2d.Reverse(x, y); //x=150, y=0
	cc2d_2.Reverse(x, y); //x=200, y=0
}

enum Format
{
	kWhd,
	kCsv,
	kSvg,
};

enum Format2
{
	kWhd2,
};
void TestEnumMgr()
{
	std::cout << typeid(Format).name() << std::endl;
	EnumMgr& enum_mgr = EnumMgr::instance();
	enum_mgr.AddEnum<Format>(kWhd, "whd");
	enum_mgr.AddEnum<Format>(kCsv, "csv");
	enum_mgr.AddEnum<Format>(kSvg, "svg");

	foreach(QString name, enum_mgr.GetNames<Format>())
	{
		qDebug() << name;
	}

}
int main(int argc, char *argv[])
{
	QCoreApplication a(argc, argv);

	TestCoordConvert2D();
	TestEnumMgr();



	return a.exec();
}
