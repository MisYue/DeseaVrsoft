#pragma once
#include "poweranalysis_global.h"
#include <QtCore>

class POWERANALYSIS_EXPORT OperatorDictionary
{
public:
	OperatorDictionary(const QString& dictionary_xml_file);
	virtual ~OperatorDictionary(void);

	//获取val
	QString GetVal(const QString& key) const
	{
		return key_2_val_and_des_.value(key.toUpper(), QPair<QString, QString>(key, QString())).first;
	}
	//获取des
	QString GetDes(const QString& key) const
	{
		return key_2_val_and_des_.value(key.toUpper(), QPair<QString, QString>(QString(), key)).second;
	}
protected:
	QString dictionary_xml_file_;	//算子字典xml文件
	QMap<QString, QPair<QString, QString> > key_2_val_and_des_;

	//解析字典文件
	void ParseDictionaryFile();
};

