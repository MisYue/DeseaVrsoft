#pragma once
#include <QtWidgets>

namespace Ui { class TaskWarheadMgr; }
struct WarheadPropertyWrap;
class TaskWarheadMgrWnd :
	public QMainWindow
{
	Q_OBJECT
public:
	TaskWarheadMgrWnd(const QString& task_guid, QWidget* parent=0);
	virtual ~TaskWarheadMgrWnd(void);
	void Init();
signals:
	void sig_current_warhead_changed(WarheadPropertyWrap* warhead_wrap);
public slots:
	void on_new();
	void on_delete();
	void on_add_exist();
	void on_current_warhead_changed(int row);
	void on_warhead_name_changed(WarheadPropertyWrap* warhead_wrap);
protected:
	Ui::TaskWarheadMgr* ui_;
	QString task_guid_;
	QMap<QString, WarheadPropertyWrap*> guid_2_warhead_wrap_;
	void CheckAndAskSave();
	WarheadPropertyWrap* GetWarheadWrap(const QString& guid);
};

