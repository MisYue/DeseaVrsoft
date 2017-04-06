//***************************************
//	创建时间:	2015:10:25   17:53
//	文件名称: 	main.cpp
//	文件作者:	岳群磊
//	
//	功能说明:	入口函数
//***************************************

#include "ImportTargetWnd.h"
#include "Frame.h"
#include <QtGui>
#include <QTranslator>
#include <QFile>
#include <QTextCodec>

int main(int argc, char *argv[])
{
	QTranslator translator;
	translator.load("qt_zh_CN.qm");
	QApplication a(argc, argv);
	QTextCodec::setCodecForCStrings(QTextCodec::codecForLocale());
	QTextCodec::setCodecForTr(QTextCodec::codecForLocale());
	a.installTranslator(&translator);
	QFile file("skin.qss");
	file.open(QFile::ReadOnly);
	QString styleSheet = QLatin1String(file.readAll());
	a.setStyleSheet(styleSheet);
	Frame frame;
	frame.setContentWidget(new TIMP::ImportTargetWnd);
	frame.showMaximized();
	return a.exec();
}
