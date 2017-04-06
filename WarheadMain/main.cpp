#include "warhead_main.h"
#include <tool/tool.h>
#include <QtGui>
#include <QtWidgets>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	//QTextCodec::setCodecForLocale(QTextCodec::codecForName("UTF-8"));
	QTextCodec::setCodecForLocale(QTextCodec::codecForName("GBK"));

#if QT_VERSION < 0x050000
	QTextCodec::setCodecForTr(QTextCodec::codecForLocale());
	QTextCodec::setCodecForCStrings(QTextCodec::codecForLocale());
#endif
	QTranslator translator;
	translator.load("qt_zh_CN.qm");
	a.installTranslator(&translator);
	QFile file("skin.qss");
	file.open(QFile::ReadOnly);
	QString styleSheet = GBK2Unicode(file.readAll());
	a.setStyleSheet(styleSheet);
	a.setOrganizationName("vrsoft");
	a.setApplicationName(GBK2Unicode("战斗部建模软件"));
	WarheadMain w;
	w.showMaximized();
	return a.exec();
}
