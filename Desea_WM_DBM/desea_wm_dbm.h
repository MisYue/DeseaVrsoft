#ifndef DESEA_WM_DBM_H
#define DESEA_WM_DBM_H

#include <QtWidgets/QMainWindow>
#include "ui_desea_wm_dbm.h"

class Desea_WM_DBM : public QMainWindow
{
	Q_OBJECT

public:
	Desea_WM_DBM(QWidget *parent = 0);
	~Desea_WM_DBM();

private:
	Ui::Desea_WM_DBMClass ui;

	//新增记录
	//导入记录
	//导出记录
	//删除记录
	//保存记录

};

#endif // DESEA_WM_DBM_H
