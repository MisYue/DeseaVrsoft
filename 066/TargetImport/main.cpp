//***************************************
//	����ʱ��:	2015:10:25   17:53
//	�ļ�����: 	main.cpp
//	�ļ�����:	��Ⱥ��
//	
//	����˵��:	��ں���
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
