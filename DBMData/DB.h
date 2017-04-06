#pragma once

#include "dbmdata_global.h"
#include <QtCore>

//ʵ�ֹ��ܣ�
//1. ��ȡ���������Ϣ
//2. �ṩ��ȡ����Ϣ�ӿ�

class TableInfo;
class DBConn;
class DBMDATA_EXPORT DB
{
public:
	DB(const QString& xml_config);
	virtual ~DB(void);

	TableInfo* GetTableInfo(const QString& table_name) { return name_2_table_.value(table_name, 0); }
protected:
	QMap<QString, TableInfo*> name_2_table_;
};

