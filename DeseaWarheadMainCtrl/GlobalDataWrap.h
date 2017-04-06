//***************************************
//	创建时间:	2017:3:16   13:04
//	文件名称: 	GlobalDataWrap.h
//	文件作者:	岳群磊
//	
//	功能说明:	全局数据包装类定义
//***************************************

#pragma once
#include <QtCore>

//存放软件的配置信息及全局数据

class DBConn;
class GlobalDataWrap
{
public:
	virtual ~GlobalDataWrap(void);
	static GlobalDataWrap& instance()
	{
		static GlobalDataWrap s_instance;
		return s_instance;
	}
	void Init(const QString& config_file = QString());
	void set_db_conn(DBConn* db_conn) { db_conn_ = db_conn; }
	DBConn* get_db_conn() { return db_conn_; }
	// 获取数据
	QString GetConfigData(const QString& key) const;
protected:
	GlobalDataWrap(void);
	DBConn* db_conn_;	//数据库连接
};

