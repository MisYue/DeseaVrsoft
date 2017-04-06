#include "dbaccess.h"
#include "DBConn.h"
#include <QtSql>

DBAccess::DBAccess(DBConn* conn)
	: conn_(conn)
{

}

DBAccess::~DBAccess()
{

}

//获取满足条件的记录
//QList<Record*> DBAccess::GetRecords(
//	const QString& table_name, 
//	const QList<QPair<QString, QVariant> >& field_names_and_values
//	) const
//{
//	return QList<Record*>();
//}

QList<Result*> DBAccess::GetResults(const QString& table_name, const QString& sql)
{
	QList<Result*> results;
	if(conn_ && conn_->IsValid())
	{
		QSqlDatabase* qdb = conn_->get_sql_db();
		Q_ASSERT(qdb && qdb->isOpen());
		QSqlQuery query(sql, *qdb);
		if(!query.exec())
		{
			qDebug() << query.lastError();
		}
		else
		{

		}
	}
	return results;
}

