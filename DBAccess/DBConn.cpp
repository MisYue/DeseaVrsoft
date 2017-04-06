#include "DBConn.h"
#include <QtSql>

DBConn::DBConn()
	: port_(1521)
	, host_name_("localhost")
	, driver_type_("QOCI")
	, qdb_(new QSqlDatabase)
{
	qDebug() << qdb_->drivers();
}



DBConn::~DBConn(void)
{
	Disconnect();
	if(qdb_)
	{
		delete qdb_;
		qdb_ = 0;
	}
}

//连接是否有效
bool DBConn::IsValid() const
{
	return (qdb_ && qdb_->isValid() && qdb_->isOpen());
}
//连接
bool DBConn::Connect()
{
	if(!qdb_->isValid())
	{
		*qdb_ = QSqlDatabase::addDatabase(driver_type_);
	}
	if(qdb_->isValid())
	{
		qdb_->setHostName(host_name_);
		qdb_->setPort(port_);
		qdb_->setDatabaseName(db_name_);
		qdb_->setUserName(user_);
		qdb_->setPassword(pwd_);
		if(!qdb_->open())
		{
			qDebug() << qdb_->lastError();
		}
		else
		{
			return true;
		}
	}

	return false;
}
//断开连接
bool DBConn::Disconnect()
{
	if(qdb_ && qdb_->isValid() && qdb_->isOpen())
	{
		qdb_->close();
	}
	return true;
}