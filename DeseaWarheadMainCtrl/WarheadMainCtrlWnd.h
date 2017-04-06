//***************************************
//	创建时间:	2017:3:14   14:13
//	文件名称: 	WarheadMainCtrlWnd.h
//	文件作者:	岳群磊
//	
//	功能说明:	战斗部主控界面类定义
//***************************************

#pragma once
#include <QtWidgets>

struct WarheadPropertyWrap;
class SingleWarheadWnd;
class TaskWarheadMgrWnd;
class WarheadMainCtrlWnd :
	public QMainWindow
{
	Q_OBJECT
public:
	WarheadMainCtrlWnd(const QString& task_guid = QString(), QWidget *parent = 0);
	virtual ~WarheadMainCtrlWnd(void);
signals:
	void sig_warhead_name_changed(WarheadPropertyWrap* warhead_wrap);
public slots:
	//设置当前战斗部
	void on_set_current_warhead(WarheadPropertyWrap* warhead_wrap);
	// 子文档激活
	void on_doc_active(QMdiSubWindow* wnd);

	// 新建
	void on_new(void);
	// 打开
	void on_open(void);
	// 导入
	void on_import(void);
	// 导出
	void on_export(void);
	// 保存
	void on_save(void);
	// 另存
	void on_save_as(void);
	// 删除
	void on_delete(void);
	// 金属材料
	void on_metal(void);
	// 装药材料
	void on_charge(void);
	// 属性
	void on_property(void);
	// 威力分析
	void on_power();
protected:
	QMdiArea* mdi_area_;
	QMap<WarheadPropertyWrap*, QMdiSubWindow*> warhead_2_sub_wnd_;
	QList<WarheadPropertyWrap*> warhead_wrap_owned_;
	TaskWarheadMgrWnd* task_wnd_;
	QString task_guid_;
	QAction* action_new_;
	QAction* action_open_;
	QAction* action_import_;
	QAction* action_export_;
	QAction* action_save_;
	QAction* action_save_as_;
	QAction* action_delete_;
	QAction* action_property_;
	QAction* action_metal_;
	QAction* action_charge_;
	QAction* action_power_;

	// 初始化
	void Init();
	// 增加文档
	QMdiSubWindow* AddDoc(WarheadPropertyWrap* warhead_wrap);
	// 删除文档
	QMdiSubWindow* DeleteDoc(WarheadPropertyWrap* warhead_wrap);
	// 更新动作状态
	void UpdateActions(void);
	// 询问是否保存
	void AskSave(WarheadPropertyWrap* warhead_wrap);
	// 是否需要保存
	bool IsNeededSave(WarheadPropertyWrap* warhead_wrap);
};

