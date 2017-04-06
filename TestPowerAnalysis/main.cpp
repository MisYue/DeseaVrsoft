#include "testpoweranalysis.h"
#include <QtWidgets>
#include <PowerAnalysis/OperatorDictionary.h>
#include <BasicTool/expandqtcore.h>
#include <PowerAnalysis/PowerAnalysisWnd.h>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	QTextCodec::setCodecForLocale(QTextCodec::codecForName("GBK"));
#if QT_VERSION < 0x050000
	QTextCodec::setCodecForTr(QTextCodec::codecForLocale());
	QTextCodec::setCodecForCStrings(QTextCodec::codecForName("UTF-8"));
#endif
	QTranslator translator;
	translator.load("qt_zh_CN.qm");
	a.installTranslator(&translator);
	QFile file("black.css");
	file.open(QFile::ReadOnly);
	QString styleSheet = ExpandQtCore::fromGBK(file.readAll().data());
	a.setStyleSheet(styleSheet);
	PowerAnalysisWnd w(ExpandQtCore::fromGBK("威力流程配置.xml"), ExpandQtCore::fromGBK("算法-字典-utf-8.xml"), 0);
	w.show();
	return a.exec();
}
