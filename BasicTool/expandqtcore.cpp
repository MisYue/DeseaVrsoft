#include "expandqtcore.h"
#include <cmath>

ExpandQtCore::ExpandQtCore()
{

}

ExpandQtCore::~ExpandQtCore()
{

}

QString ExpandQtCore::fromGBK(const char* str)
{
	QTextCodec* gbk = QTextCodec::codecForName("GBK");
	return gbk->toUnicode(str);
}
QByteArray ExpandQtCore::toGBK(const QString& str)
{
	QTextCodec* gbk = QTextCodec::codecForName("GBK");
	return gbk->fromUnicode(str.data(), str.size());
}
// 获取后缀
QString ExpandQtCore::getSuffix(const QString& str, char sep)
{
	int index = str.lastIndexOf(sep);
	return str.right(str.size()-index-1);
}

// 去除小数末尾0
QString ExpandQtCore::removeDecimalEndZero(double d, int precision_hint)
{
	QString label = QString::number(d, 'f', precision_hint);
	int i = 0;
	for(i=label.size()-1; i>-1; i--)
	{
		if(label[i] != '0')
			break;
	}
	if(label[i] == '.')
		--i;
	return label.left(i+1);
}

