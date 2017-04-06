//战斗部主控类定义文件

#ifndef DESEAWARHEADMAINCTRL_H
#define DESEAWARHEADMAINCTRL_H

#include <QtWidgets>
#include "ui_deseawarheadmainctrl.h"

class DBConn;
class WarheadProperty;
class WarheadDrawWnd;

//多文档实现，支持同时打开多个战斗部
class DeseaWarheadMainCtrl : public QMainWindow
{
	Q_OBJECT
public:
	DeseaWarheadMainCtrl(DBConn* db_conn, const QString& task_guid = QString(), QWidget *parent = 0);
	~DeseaWarheadMainCtrl();
public slots:
	//新建战斗部
	void on_new();
	//保存战斗部到数据库
	void on_save();
	//另存战斗部到数据库
	void on_save_as();
	//导出战斗部结构到文件
	void on_export();
	//导出战斗部威力到文件
	void on_export_power();
	//从数据库中选择一个战斗部打开
	void on_open();
	//从数据库中打开指定战斗部
	void on_open(const QString& guid);
	//从文件导入战斗部结构
	void on_import();
	//查看金属材料
	void on_metal_material();
	//查看装药材料
	void on_charge_material();
	//查看战斗部属性
	void on_view_warhead_property();
	//威力分析
	void on_power_analysis();

	//设置当前战斗部
	void on_set_current_warhead(WarheadProperty* warhead);

protected:
	void closeEvent(QCloseEvent * event);
private:
	Ui::DeseaWarheadMainCtrlClass ui;
	DBConn* db_conn_;
	QString task_guid_;
	WarheadProperty* warhead_;
	WarheadDrawWnd* warhead_draw_wnd_;
	bool task_exist_;

	QMdiArea* mdi_area_;	//多文档管理器
	QMap<WarheadProperty*, QMdiSubWindow*> warhead_2_doc_;	//key:战斗部属性 value:文档

	///////私有成员函数////////
	void InitUi();
	void UpdateActionEnabled();

	//增加文档
	QMdiSubWindow* AddDoc(WarheadProperty* warhead);
	//删除文档
	QMdiSubWindow* DeleteDoc(WarheadProperty* warhead);
	//检查及询问是否保存
	void CheckAndAskSave(WarheadProperty* warhead);
};

#endif // DESEAWARHEADMAINCTRL_H
