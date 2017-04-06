#ifndef EXPANDQTCORE_H
#define EXPANDQTCORE_H

#include "basictool_global.h"
#include <QtCore>
#include <string>

class BASICTOOL_EXPORT ExpandQtCore
{
public:
	ExpandQtCore();
	~ExpandQtCore();
	// GBK->Unicode
	static QString fromGBK(const char* str);
	// Unicode->GBK
	static QByteArray toGBK(const QString& str);
	// 获取后缀
	static QString getSuffix(const QString& str, char sep = '.');
	// 去除小数末尾0
	static QString removeDecimalEndZero(double d, int precision_hint = 6);
};

#endif // EXPANDQTCORE_H
