#include "warheaddbaccess.h"
#include <WarheadDataEntity/warheaddataentity.h>
#include <BasicTool/GlobalData.h>
#include <BasicTool/expandqtcore.h>
#include <DBAccess/DBConn.h>
#include <WarheadFileReadWrite/warheadfilereadwriteengine.h>
#include <QtSql>

WarheadDBAccess::WarheadDBAccess(DBConn* db_conn)
	: db_conn_(db_conn)
{

}

WarheadDBAccess::~WarheadDBAccess()
{

}


// 是否存在
bool WarheadDBAccess::IsExist(const QString& guid)
{
	if(db_conn_ && db_conn_->IsValid() && !guid.isEmpty())
	{
		QSqlDatabase* qdb = db_conn_->get_sql_db();
		QString sql = GlobalData::instance().GetConfigData("1");
		QSqlQuery query(sql.arg(guid), *qdb);
		if(query.first())
			return true;
	}
	return false;
}


// 获取新建战斗部id
int WarheadDBAccess::GetNewId(void)
{
	if(db_conn_ && db_conn_->IsValid())
	{
		QSqlDatabase* qdb = db_conn_->get_sql_db();
		QString sql = GlobalData::instance().GetConfigData("2");
		QSqlQuery query(sql, *qdb);
		if(query.first())
			return query.value(0).toInt()+1;
	}
	return 0;
}


// 写入战斗部
bool WarheadDBAccess::Write(const WarheadDataEntity* warhead)
{
	bool result = false;
	if(db_conn_ && db_conn_->IsValid())
	{
		const WarheadExtraProperty* extra_prop = warhead->get_extra_property();
		QSqlDatabase* qdb = db_conn_->get_sql_db();
		QString sql = GlobalData::instance().GetConfigData("3");
		QSqlQuery query(*qdb);
		query.prepare(sql);
		query.bindValue(":1", extra_prop->get_id());
		query.bindValue(":2", extra_prop->get_guid());
		query.bindValue(":3", extra_prop->get_name());
		query.bindValue(":4", extra_prop->get_task_guid());
		query.bindValue(":5", extra_prop->get_country());
		query.bindValue(":6", extra_prop->get_sub_class_guid());
		query.bindValue(":7", extra_prop->get_describe());
		query.bindValue(":8", extra_prop->get_missile_name());
		query.bindValue(":9", extra_prop->get_service_start_date());
		query.bindValue(":10", extra_prop->get_service_end_date());
		WarheadFileReadWriteEngine writer_engine;
		WarheadDataEntityWrap warhead_wrap;
		warhead_wrap.warhead = warhead;
		QString structure = writer_engine.WriteString(&warhead_wrap, WarheadFileReadWriteEngine::kWhd);
		QString power = writer_engine.WriteString(&warhead_wrap, WarheadFileReadWriteEngine::kPwr);
		query.bindValue(":11", structure);
		query.bindValue(":12", power);
		query.bindValue(":13", extra_prop->get_create_time());
		query.bindValue(":14", extra_prop->get_update_time());
		query.bindValue(":15", extra_prop->get_share() ? 1 : 0);
		result = query.exec();
		if(!result)
		{
			qDebug() << ExpandQtCore::fromGBK("写入战斗部失败！") << query.lastError();
		}
	}
	return result;
}


// 读取战斗部
WarheadDataEntity* WarheadDBAccess::Read(const QString& guid)
{
	WarheadDataEntity* result = NULL;
	if(db_conn_ && db_conn_->IsValid() && !guid.isEmpty())
	{
		QSqlDatabase* qdb = db_conn_->get_sql_db();
		QString sql = GlobalData::instance().GetConfigData("1");
		QSqlQuery query(sql.arg(guid), *qdb);
		if(query.first())
		{
			WarheadFileReadWriteEngine writer_engine;
			result = writer_engine.ReadString(query.value(10).toString(), WarheadFileReadWriteEngine::kWhd);
			if(!result)
			{
				//读取结构失败
				result = new WarheadDataEntity;
			}
			WarheadExtraProperty* extra_prop = result->get_extra_property();
			extra_prop->set_id(query.value(0).toInt());
			extra_prop->set_guid(query.value(1).toString());
			extra_prop->set_name(query.value(2).toString());
			extra_prop->set_task_guid(query.value(3).toString());
			extra_prop->set_country(query.value(4).toString());
			extra_prop->set_sub_class_guid(query.value(5).toString());
			extra_prop->set_describe(query.value(6).toString());
			extra_prop->set_missile_name(query.value(7).toString());
			extra_prop->set_service_start_date(query.value(8).toDate());
			extra_prop->set_service_end_date(query.value(9).toDate());
			//extra_prop->set_power_csv(query.value(11).toString());
			extra_prop->set_create_time(query.value(12).toDateTime());
			extra_prop->set_update_time(query.value(13).toDateTime());
			extra_prop->set_share(query.value(14).toInt() ? true : false);
		}
	}
	return result;
}


// 获取战斗部所有类别GUID和名称
void WarheadDBAccess::GetClassGuidAndNames(QMap<QString, QString>& guid_and_names)
{
	guid_and_names.clear();
	if(db_conn_ && db_conn_->IsValid())
	{
		QSqlDatabase* qdb = db_conn_->get_sql_db();
		QString sql = GlobalData::instance().GetConfigData("4");
		QSqlQuery query(sql, *qdb);
		while(query.next())
		{
			guid_and_names.insert(query.value(0).toString(), query.value(1).toString());
		}
	}
}


// 获取战斗部二级类别GUID和名称
void WarheadDBAccess::GetSubClassGuidAndNames(const QString& class_guid, QMap<QString, QString>& guid_and_names)
{
	guid_and_names.clear();
	if(db_conn_ && db_conn_->IsValid())
	{
		QSqlDatabase* qdb = db_conn_->get_sql_db();
		QString sql = GlobalData::instance().GetConfigData("5");
		QSqlQuery query(sql.arg(class_guid), *qdb);
		while(query.next())
		{
			guid_and_names.insert(query.value(0).toString(), query.value(1).toString());
		}
	}
}

// 获取战斗部二级类别名称
QString WarheadDBAccess::GetSubClassName(const QString& guid)
{
	if(db_conn_ && db_conn_->IsValid())
	{
		QSqlDatabase* qdb = db_conn_->get_sql_db();
		QString sql = GlobalData::instance().GetConfigData("8");
		QSqlQuery query(sql.arg(guid), *qdb);
		if(query.next())
		{
			return query.value(0).toString();
		}
	}
	return QString();
}
// 获取战斗部一级类别GUID和名称
void WarheadDBAccess::GetClassGuidAndName(const QString& sub_class_guid, QString& class_guid, QString& class_name)
{
	if(db_conn_ && db_conn_->IsValid())
	{
		QSqlDatabase* qdb = db_conn_->get_sql_db();
		QString sql = GlobalData::instance().GetConfigData("9");
		QSqlQuery query(sql.arg(sub_class_guid), *qdb);
		if(query.next())
		{
			class_guid = query.value(0).toString();
			sql = GlobalData::instance().GetConfigData("10");
			if(query.exec(sql.arg(class_guid)))
			{
				if(query.next())
				{
					class_name = query.value(0).toString();
				}
			}
		}
	}
}

// 获取战斗部二级类别Guid
QString WarheadDBAccess::GetSubClassGuid(const QString& name)
{
	if(db_conn_ && db_conn_->IsValid())
	{
		QSqlDatabase* qdb = db_conn_->get_sql_db();
		QString sql = GlobalData::instance().GetConfigData("11");
		QSqlQuery query(sql.arg(name), *qdb);
		if(query.next())
		{
			return query.value(0).toString();
		}
	}
	return QString();
}