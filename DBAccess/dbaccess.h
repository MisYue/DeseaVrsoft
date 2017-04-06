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

	//获取满足条件的记录
	////field_names_and_values = QList<QPair<QString, QVariant> >()时，获取表中所有记录
	//QList<Record*> GetRecords(
	//	const QString& table_name, 
	//	const QList<QPair<QString, QVariant> >& field_names_and_values = QList<QPair<QString, QVariant> >()
	//	) const;

	QList<Result*> GetResults(const QString& table_name, const QString& sql);

protected:
	DBConn* conn_;

};

#endif // DBACCESS_H
