#pragma once

#include "dbmdata_global.h"
#include <QtCore>

//实现功能：
//1. 读取表的配置信息
//2. 提供获取表信息接口

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

