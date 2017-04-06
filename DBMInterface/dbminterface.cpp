#include "dbminterface.h"
#include <DBAccess/DBConn.h>
#include <DBAccess/dbaccess.h>
#include <DBMUi/DBView.h>
#include <DBMUi/SaveDlg.h>
#include <DBMUi/SelectView.h>
#include <DBMUi/DBConnDlg.h>

DBMInterface::DBMInterface()
	: db_conn_(new DBConn)
{

}

DBMInterface::DBMInterface(
	const QString& db_name, 
	const QString& user, 
	const QString& pwd, 
	const QString& host_name, 
	int port, 
	const QString& driver_type
	)
	: db_conn_(new DBConn)
{
	db_conn_->set_db_name(db_name);
	db_conn_->set_driver_type(driver_type);
	db_conn_->set_host_name(host_name);
	db_conn_->set_user(user);
	db_conn_->set_pwd(pwd);
	db_conn_->set_port(port);

	db_conn_->Connect();

}

DBMInterface::~DBMInterface()
{
	if(db_conn_)
	{
		delete db_conn_;
		db_conn_ = 0;
	}
}

bool DBMInterface::IsConnect() const 
{
	return db_conn_&&db_conn_->IsValid();
}

//设置连接
bool DBMInterface::SetDBConnect(const QString& db_name, const QString& user, const QString& pwd)
{
	if(!db_name.isEmpty())
		db_conn_->set_db_name(db_name);
	if(!user.isEmpty())
		db_conn_->set_user(user);
	if(!pwd.isEmpty())
		db_conn_->set_pwd(pwd);
	DBConnDlg conn_dlg(db_conn_);
	return (QDialog::Accepted == conn_dlg.exec());
}
//查看所有记录
void DBMInterface::ViewAllRecords()
{
	if(CheckConn())
	{
		DBView db_view;
		db_view.exec();
	}
}
//保存记录
bool DBMInterface::SaveRecord(const QString& table_name, const QList<QPair<QString, QVariant> >& field_names_and_values)
{
	if(CheckConn())
	{
		SaveDlg save_dlg(table_name, field_names_and_values);
		return (QDialog::Accepted == save_dlg.exec());
	}
	return false;
}
//选择一条记录
Record* DBMInterface::SelectRecord()
{
	if(CheckConn())
	{
		SelectView select_view;
		return select_view.SelectRecord();
	}
	return 0;
}
//获取满足条件的记录
QList<Record*> DBMInterface::GetRecords(const QString& table_name, const QList<QPair<QString, QVariant> >& field_names_and_values)
{
	if(CheckConn())
	{
		DBAccess db_access(db_conn_);
		return db_access.GetRecords(table_name, field_names_and_values);
	}
	return QList<Record*>();
}

//销毁记录对象，释放内存
void DBMInterface::DestroyRecord(Record* record)
{
	if(record)
	{
		delete record;
		record = 0;
	}
}

bool DBMInterface::CheckConn()
{
	if(!db_conn_->IsValid())
	{
		if(false == db_conn_->Connect())
		{
			DBConnDlg conn_dlg(db_conn_);
			return (QDialog::Accepted == conn_dlg.exec());
		}
	}
	return true;
}

