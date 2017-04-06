#ifndef DBMINTERFACE_H
#define DBMINTERFACE_H

#include "dbminterface_global.h"
#include <QtCore>

class DBConn;
class Record;

class DBMINTERFACE_EXPORT DBMInterface
{
public:
	DBMInterface();
	DBMInterface(const QString& db_name, 
		const QString& user, 
		const QString& pwd, 
		const QString& host_name = QString("localhost"), 
		int port = 1521, 
		const QString& driver_type = QString("QOCI")
		);
	~DBMInterface();

	bool IsConnect() const ;
	//设置连接
	bool SetDBConnect(const QString& db_name=QString(), const QString& user=QString(), const QString& pwd=QString());
	//查看所有记录
	void ViewAllRecords();
	//保存记录
	bool SaveRecord(const QString& table_name, const QList<QPair<QString, QVariant> >& field_names_and_values);
	//选择一条记录
	Record* SelectRecord();
	//获取满足条件的记录
	//field_names_and_values = QList<QPair<QString, QVariant> >()时，获取表中所有记录
	QList<Record*> GetRecords(const QString& table_name, const QList<QPair<QString, QVariant> >& field_names_and_values = QList<QPair<QString, QVariant> >());
	//销毁记录对象，释放内存
	static void DestroyRecord(Record* record);


private:
	DBConn* db_conn_;	//数据库连接

	bool CheckConn();
};

#endif // DBMINTERFACE_H
