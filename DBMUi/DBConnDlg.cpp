#include "DBConnDlg.h"
#include "ui_DBConn.h"
#include <DBAccess/DBConn.h>
#include <BasicTool/expandqtcore.h>

DBConnDlg::DBConnDlg(DBConn* conn)
	: conn_(conn)
	, ui_(new Ui::DBConn)
{
	Q_ASSERT(conn_);
	ui_->setupUi(this);
	ui_->lineEdit_db_name->setText(conn_->get_db_name());
	ui_->lineEdit_user->setText(conn_->get_user());
	ui_->lineEdit_pwd->setText(conn_->get_pwd());
}


DBConnDlg::~DBConnDlg(void)
{
	delete ui_;
}

void DBConnDlg::accept()
{
	conn_->set_pwd(ui_->lineEdit_pwd->text());
	conn_->set_user(ui_->lineEdit_user->text());
	conn_->set_db_name(ui_->lineEdit_db_name->text());
	conn_->set_host_name(ui_->lineEdit_host_name->text());
	conn_->set_port(ui_->spinBox_port->value());

	if(conn_->Connect())
	{
		QDialog::accept();
	}
	else
	{
		QMessageBox box(this);
		box.setIcon(QMessageBox::Critical);
		box.addButton(ExpandQtCore::fromGBK("确定"), QMessageBox::AcceptRole);
		box.setText(ExpandQtCore::fromGBK("数据库连接失败！"));
		box.setWindowTitle(ExpandQtCore::fromGBK("错误"));
		box.exec();
	}
}

