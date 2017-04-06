#pragma once
#include <QtWidgets>


//实现功能：
//1. 显示查询结果
//2. 当用户选定一条结果时，发出信号，将结果作为信号参数传出

class DBConn;
class QueryResultShowWgt :
	public QWidget
{
	Q_OBJECT
public:
	QueryResultShowWgt(DBConn* db_conn, QString& table_name=QString(), QWidget* parent=0);
	virtual ~QueryResultShowWgt(void);
	void SetSql(const QString& sql);
signals:
	void sig_current_selected_result_changed(const QString& current_selected);
private slots:
	void on_current_selected_changed(int current_row);
protected:
	QString table_name_;
	DBConn* db_conn_;
	QListWidget* list_wgt_;
};

