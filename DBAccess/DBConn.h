#pragma once

#include "dbaccess_global.h"
#include <QtCore>

class QSqlDatabase;
class DBACCESS_EXPORT DBConn
{
public:
	DBConn();

	virtual ~DBConn(void);


	//连接是否有效
	bool IsValid() const;
	//连接
	bool Connect();
	//断开连接
	bool Disconnect();

	QSqlDatabase* get_sql_db() { return qdb_; }

	void set_host_name(const QString& host_name) { host_name_ = host_name; }
	QString get_host_name() const { return host_name_; }

	void set_port(int port) { port_ = port; }
	int get_port() const { return port_; }

	void set_db_name(const QString& db_name) { db_name_ = db_name; }
	QString get_db_name() const { return db_name_; }

	void set_user(const QString& user) { user_ = user; }
	QString get_user() const { return user_; }

	void set_pwd(const QString& pwd) { pwd_ = pwd; }
	QString get_pwd() const { return pwd_; }

	void set_driver_type(const QString& driver_type) { driver_type_ = driver_type; }
	QString get_driver_type() const { return driver_type_; }

protected:
	int port_;
	QString driver_type_;
	QString host_name_;
	QString db_name_;
	QString user_;
	QString pwd_;
	QSqlDatabase* qdb_;
};

