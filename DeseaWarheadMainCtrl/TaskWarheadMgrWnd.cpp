#include "TaskWarheadMgrWnd.h"
#include "ui_taskwarheadmgr.h"
#include "GlobalDataWrap.h"
#include "WarheadPropertyDlg.h"
#include <WarheadDataEntity/warheaddataentity.h>
#include <DBAccess/DBConn.h>
#include <QtSql>
#include <BasicTool/expandqtcore.h>
#include <BasicTool/expandqtgui.h>
#include <TaskDBAccess/taskdbaccess.h>
#include <WarheadDBAccess/warheaddbaccess.h>

TaskWarheadMgrWnd::TaskWarheadMgrWnd(const QString& task_guid, QWidget* parent)
	: QMainWindow(parent)
	, task_guid_(task_guid)
	, ui_(new Ui::TaskWarheadMgr)
{
	ui_->setupUi(this);
}


TaskWarheadMgrWnd::~TaskWarheadMgrWnd(void)
{
	CheckAndAskSave();
	delete ui_;
}


void TaskWarheadMgrWnd::Init()
{
	//����
	QAction* new_action = ExpandQtGui::createAction(ExpandQtCore::fromGBK("�½�"), this, SLOT(on_new()), this);
	QAction* add_exist_action = ExpandQtGui::createAction(ExpandQtCore::fromGBK("�����ݿ����"), this, SLOT(on_add_exist()), this);
	QAction* delete_action = ExpandQtGui::createAction(ExpandQtCore::fromGBK("ɾ��"), this, SLOT(on_delete()), this);
	QToolBar* tool_bar = new QToolBar(this);
	addToolBar(Qt::TopToolBarArea, tool_bar);
	tool_bar->addAction(new_action);
	tool_bar->addAction(add_exist_action);
	tool_bar->addAction(delete_action);
	DBConn* db_conn = GlobalDataWrap::instance().get_db_conn();
	TaskDBAccess task_db(db_conn);
	setWindowTitle(ExpandQtCore::fromGBK("����'%1'��ս�����б�").arg(task_db.GetName(task_guid_)));
	//��ȡ�����µ�ս����
	QMap<QString, QString> guid_and_names;
	task_db.GetWarheadGuidAndNames(guid_and_names);
	for(QMap<QString, QString>::iterator beg = guid_and_names.begin(); beg != guid_and_names.end(); ++beg)
	{
		QListWidgetItem* item = new QListWidgetItem(beg.value());
		item->setData(Qt::UserRole, beg.key());
		ui_->listWidget->addItem(item);
	}
	connect(ui_->listWidget, SIGNAL(currentRowChanged(int)), this, SLOT(on_current_warhead_changed(int)));
	ui_->listWidget->setCurrentRow(0);
}

///slots
void TaskWarheadMgrWnd::on_new()
{
	WarheadPropertyWrap* warhead_wrap = new WarheadPropertyWrap;
	warhead_wrap->warhead = new WarheadDataEntity;
	WarheadPropertyDlg dlg(warhead_wrap, WarheadPropertyDlg::kCreate, this);
	if(QDialog::Accepted == dlg.exec())
	{
		WarheadExtraProperty* prop = warhead_wrap->warhead->get_extra_property();
		QString name = prop->get_name();
		QListWidgetItem* item = new QListWidgetItem(name);
		item->setData(Qt::UserRole, QVariant(reinterpret_cast<qlonglong>(warhead_wrap)));
		ui_->listWidget->addItem(item);
		ui_->listWidget->setCurrentItem(item);
	}
	else
	{
		delete warhead_wrap->warhead;
		delete warhead_wrap;
	}
}
void TaskWarheadMgrWnd::on_delete()
{

}
void TaskWarheadMgrWnd::on_add_exist()
{

}
void TaskWarheadMgrWnd::on_current_warhead_changed(int row)
{
	QListWidgetItem* item = ui_->listWidget->currentItem();
	QString guid = item->data(Qt::UserRole).toString();
	WarheadPropertyWrap* warhead_wrap = GetWarheadWrap(guid);
	if(warhead_wrap)
		emit sig_current_warhead_changed(warhead_wrap);
}
void TaskWarheadMgrWnd::on_warhead_name_changed(WarheadPropertyWrap* warhead_wrap)
{
	for(int i=0, n=ui_->listWidget->count(); i<n; ++i)
	{
		QListWidgetItem* item = ui_->listWidget->item(i);
		WarheadPropertyWrap* _warhead_wrap = reinterpret_cast<WarheadPropertyWrap*>(item->data(Qt::UserRole).toLongLong());
		Q_ASSERT(_warhead_wrap);
		if(warhead_wrap == _warhead_wrap)
		{
			item->setText(warhead_wrap->warhead->get_extra_property()->get_name());
			break;
		}
	}
}
//protected
void TaskWarheadMgrWnd::CheckAndAskSave()
{

}

WarheadPropertyWrap* TaskWarheadMgrWnd::GetWarheadWrap(const QString& guid)
{
	WarheadPropertyWrap* warhead_wrap = guid_2_warhead_wrap_.value(guid, 0);
	if(!warhead_wrap)
	{
		//�����ݿ��ȡ
		warhead_wrap = new WarheadPropertyWrap;
		WarheadDBAccess warhead_db(GlobalDataWrap::instance().get_db_conn());
		warhead_wrap->warhead = warhead_db.Read(guid);
		guid_2_warhead_wrap_.insert(guid, warhead_wrap);
	}
	return warhead_wrap;
}
