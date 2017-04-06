//***************************************
//	����ʱ��:	2017:3:16   13:04
//	�ļ�����: 	GlobalDataWrap.h
//	�ļ�����:	��Ⱥ��
//	
//	����˵��:	ȫ�����ݰ�װ�ඨ��
//***************************************

#pragma once
#include <QtCore>

//��������������Ϣ��ȫ������

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
	// ��ȡ����
	QString GetConfigData(const QString& key) const;
protected:
	GlobalDataWrap(void);
	DBConn* db_conn_;	//���ݿ�����
};

