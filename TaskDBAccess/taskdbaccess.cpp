#include "taskdbaccess.h"
#include <BasicTool/expandqtcore.h>
#include <BasicTool/GlobalData.h>
#include <DBAccess/DBConn.h>
#include <QtSql>

TaskDBAccess::TaskDBAccess(DBConn* db_conn)
	: db_conn_(db_conn)
{

}

TaskDBAccess::~TaskDBAccess()
{

}

// 查询任务是否存在
bool TaskDBAccess::IsExist(const QString& guid)
{
	if(db_conn_ && db_conn_->IsValid() && !guid.isEmpty())
	{
		QSqlDatabase* qdb = db_conn_->get_sql_db();
		QString sql = GlobalData::instance().GetConfigData("0");
		QSqlQuery query(sql.arg(guid), *qdb);
		if(query.first())
			return true;
	}
	return false;
}

// 获取任务名称
QString TaskDBAccess::GetName(const QString& guid)
{
	if(db_conn_ && db_conn_->IsValid() && !guid.isEmpty())
	{
		QSqlDatabase* qdb = db_conn_->get_sql_db();
		QString sql = GlobalData::instance().GetConfigData("0");
		QSqlQuery query(sql.arg(guid), *qdb);
		if(query.first())
			return query.value(0).toString();
	}
	return QString();
}

// 获取所有任务guid和名称
void TaskDBAccess::GetGuidAndNames(QMap<QString, QString>& guid_and_names)
{
	guid_and_names.clear();
	if(db_conn_ && db_conn_->IsValid())
	{
		QSqlDatabase* qdb = db_conn_->get_sql_db();
		QString sql = GlobalData::instance().GetConfigData("6");
		QSqlQuery query(sql, *qdb);
		while(query.next())
		{
			guid_and_names.insert(query.value(0).toString(), query.value(1).toString());
		}
	}
}
// 获取任务下的战斗部guid和名称
void TaskDBAccess::GetWarheadGuidAndNames(QMap<QString, QString>& guid_and_names)
{
	guid_and_names.clear();
	if(db_conn_ && db_conn_->IsValid())
	{
		QSqlDatabase* qdb = db_conn_->get_sql_db();
		QString sql = GlobalData::instance().GetConfigData("7");
		QSqlQuery query(sql, *qdb);
		while(query.next())
		{
			guid_and_names.insert(query.value(0).toString(), query.value(1).toString());
		}
	}
}