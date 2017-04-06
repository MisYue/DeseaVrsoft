#include "desea_wm_dbm.h"
#include <QtWidgets>
#include <DBMInterface/dbminterface.h>
#include <BasicTool/expandqtcore.h>
#include <DBMData/ExpandType.h>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	//Desea_WM_DBM w;
	//w.show();
	QTextCodec::setCodecForLocale(QTextCodec::codecForName("GBK"));

#if QT_VERSION < 0x050000
	QTextCodec::setCodecForTr(QTextCodec::codecForLocale());
	QTextCodec::setCodecForCStrings(QTextCodec::codecForName("UTF-8"));
#endif
	QTranslator translator;
	translator.load("qt_zh_CN.qm");
	a.installTranslator(&translator);
	QFile file("skin.qss");
	file.open(QFile::ReadOnly);
	QString styleSheet = ExpandQtCore::fromGBK(file.readAll().data());
	a.setStyleSheet(styleSheet);


	//测试扩展类型
	ExpandType::AddType("xml");
	ExpandType::AddType("csv");
	ExpandType::AddType("wms");

	ExpandType expand_type("xml", QByteArray("test"));
	QVariant var = QVariant::fromValue<ExpandType>(expand_type);
	ExpandType expand_type_2 = var.value<ExpandType>();

	Q_ASSERT(expand_type_2 == expand_type);


	//测试接口
	DBMInterface dbm_interface;

	if(dbm_interface.SetDBConnect("myorcl", "system", "myorcl"))
	{
		dbm_interface.ViewAllRecords();
	}
	else
	{
		qWarning() << "Connect DB Error!";
	}

	return 0;
	//return a.exec();
}
