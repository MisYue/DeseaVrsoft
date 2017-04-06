#include "QueryResultShowWgt.h"
#include <BasicTool/expandqtcore.h>
#include <DBAccess/DBConn.h>
#include <QtSql>

QueryResultShowWgt::QueryResultShowWgt(DBConn* db_conn, QString& table_name, QWidget* parent)
	: QWidget(parent)
	, table_name_(table_name)
	, db_conn_(db_conn)
{
	setWindowTitle(ExpandQtCore::fromGBK("查询结果列表"));

	QHBoxLayout* layout = new QHBoxLayout(this);

	list_wgt_ = new QListWidget(this);
	layout->addWidget(list_wgt_);

	connect(list_wgt_, SIGNAL(currentRowChanged(int)), this, SLOT(on_current_selected_changed(int)));
}


QueryResultShowWgt::~QueryResultShowWgt(void)
{
}

void QueryResultShowWgt::SetSql(const QString& sql)
{
	list_wgt_->clear();
	if(db_conn_ && db_conn_->IsValid())
	{
		QSqlDatabase* qdb = db_conn_->get_sql_db();
		QSqlQuery query(sql, *qdb);
		while(query.next())
		{
			list_wgt_->addItem(query.value(0).toString());
		}

	}
}

void QueryResultShowWgt::on_current_selected_changed(int current_row)
{
	QString current_selected = list_wgt_->currentItem()->text();
	emit sig_current_selected_result_changed(current_selected);
}


