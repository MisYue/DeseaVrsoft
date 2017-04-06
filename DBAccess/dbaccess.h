#ifndef DBACCESS_H
#define DBACCESS_H

#include "dbaccess_global.h"
#include <QtCore>

class Result;
class DBConn;
class DBACCESS_EXPORT DBAccess
{
public:
	DBAccess(DBConn* conn);
	~DBAccess();

	//��ȡ���������ļ�¼
	////field_names_and_values = QList<QPair<QString, QVariant> >()ʱ����ȡ�������м�¼
	//QList<Record*> GetRecords(
	//	const QString& table_name, 
	//	const QList<QPair<QString, QVariant> >& field_names_and_values = QList<QPair<QString, QVariant> >()
	//	) const;

	QList<Result*> GetResults(const QString& table_name, const QString& sql);

protected:
	DBConn* conn_;

};

#endif // DBACCESS_H
