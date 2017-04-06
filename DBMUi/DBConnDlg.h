#pragma once

#include "dbmui_global.h"
#include <QtWidgets>


class DBConn;
namespace Ui
{
	class DBConn;
}
class DBMUI_EXPORT DBConnDlg :
	public QDialog
{
public:
	DBConnDlg(DBConn* conn);
	virtual ~DBConnDlg(void);
	
	virtual void accept();
protected:
	DBConn* conn_;
	Ui::DBConn* ui_;
};

