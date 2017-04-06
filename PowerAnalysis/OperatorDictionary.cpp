#include "OperatorDictionary.h"
#include <QtXml>
#include <BasicTool/expandqtcore.h>

OperatorDictionary::OperatorDictionary(const QString& dictionary_xml_file)
	: dictionary_xml_file_(dictionary_xml_file)
{
	ParseDictionaryFile();
}


OperatorDictionary::~OperatorDictionary(void)
{
}

//�����ֵ��ļ�
void OperatorDictionary::ParseDictionaryFile()
{
	if(dictionary_xml_file_.isEmpty())
	{
		qWarning() << ExpandQtCore::fromGBK("δָ�������ֵ��ļ�!");
		return ;
	}
	if(!QFile::exists(dictionary_xml_file_))
	{
		qWarning() << ExpandQtCore::fromGBK("�����ֵ��ļ�'%1'������!").arg(dictionary_xml_file_);
		return ;
	}

	QDomDocument doc;
	QFile file(dictionary_xml_file_);
	bool ok = false;
	if (file.open(QIODevice::ReadOnly))
	{
		if (doc.setContent(&file)) 
		{
			ok = true;
		}
	}
	if(!ok)
	{
		qWarning() << ExpandQtCore::fromGBK("�������ֵ��ļ�'%1'ʧ��!").arg(dictionary_xml_file_);
		return ;
	}
	QDomElement root = doc.documentElement();
	for(QDomElement element = root.firstChildElement(); !element.isNull(); element = element.nextSiblingElement())
	{
		QString key = element.attribute("key").toUpper();
		QString val = element.attribute("val");
		QString des = element.attribute("des");
		key_2_val_and_des_.insert(key, qMakePair<QString, QString>(val, des));
	}
}
