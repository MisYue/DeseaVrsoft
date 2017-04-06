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
	//��������
	bool SetDBConnect(const QString& db_name=QString(), const QString& user=QString(), const QString& pwd=QString());
	//�鿴���м�¼
	void ViewAllRecords();
	//�����¼
	bool SaveRecord(const QString& table_name, const QList<QPair<QString, QVariant> >& field_names_and_values);
	//ѡ��һ����¼
	Record* SelectRecord();
	//��ȡ���������ļ�¼
	//field_names_and_values = QList<QPair<QString, QVariant> >()ʱ����ȡ�������м�¼
	QList<Record*> GetRecords(const QString& table_name, const QList<QPair<QString, QVariant> >& field_names_and_values = QList<QPair<QString, QVariant> >());
	//���ټ�¼�����ͷ��ڴ�
	static void DestroyRecord(Record* record);


private:
	DBConn* db_conn_;	//���ݿ�����

	bool CheckConn();
};

#endif // DBMINTERFACE_H
