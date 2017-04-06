#pragma once
#include "poweranalysis_global.h"
#include <QtCore>

class POWERANALYSIS_EXPORT OperatorDictionary
{
public:
	OperatorDictionary(const QString& dictionary_xml_file);
	virtual ~OperatorDictionary(void);

	//��ȡval
	QString GetVal(const QString& key) const
	{
		return key_2_val_and_des_.value(key.toUpper(), QPair<QString, QString>(key, QString())).first;
	}
	//��ȡdes
	QString GetDes(const QString& key) const
	{
		return key_2_val_and_des_.value(key.toUpper(), QPair<QString, QString>(QString(), key)).second;
	}
protected:
	QString dictionary_xml_file_;	//�����ֵ�xml�ļ�
	QMap<QString, QPair<QString, QString> > key_2_val_and_des_;

	//�����ֵ��ļ�
	void ParseDictionaryFile();
};

