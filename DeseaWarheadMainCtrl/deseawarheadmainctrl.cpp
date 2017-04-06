#include "deseawarheadmainctrl.h"
#include "WarheadProperty.h"
#include "TaskWarheadMgrWnd.h"
#include "MaterialViewDlg.h"
#include "WarheadPropertyDlg.h"
#include "GlobalTool.h"
#include <ExpandQtCore/expandqtcore.h>
#include <ExpandQtGui/expandqtgui.h>
#include <WarheadDraw/warhead_draw_wnd.h>
#include <WarheadReadWrite/warhead_read.h>
#include <PowerAnalysis/PowerAnalysisWgt.h>
#include <WarheadModelData/warhead_model.h>
#include <QtSql>

DeseaWarheadMainCtrl::DeseaWarheadMainCtrl(DBConn* db_conn, const QString& task_guid, QWidget *parent)
	: QMainWindow(parent)
	, db_conn_(db_conn)
	, task_guid_(task_guid)
	, warhead_(0)
	, task_exist_(!task_guid.isEmpty())
	, mdi_area_(new QMdiArea)
{
	//ui.setupUi(this);
	Q_ASSERT(db_conn_);
	InitUi();
}
DeseaWarheadMainCtrl::~DeseaWarheadMainCtrl()
{

}
void DeseaWarheadMainCtrl::InitUi()
{
	//QHBoxLayout* layout = new QHBoxLayout(ui.centralWidget);
	//layout->setContentsMargins(0, 0, 0, 0);
	//layout->addWidget(mdi_area_);
	mdi_area_->setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);
	mdi_area_->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
	setCentralWidget(mdi_area_);
	//建模模块
	//warhead_draw_wnd_ = new WarheadDrawWnd(WarheadDrawWnd::kEdit, 0);
	//mdi_area_->addSubWindow(warhead_draw_wnd_);

	//layout->addWidget(warhead_draw_wnd_);
	//任务对应的战斗部列表
	if(!task_guid_.isEmpty())
	{
		TaskWarheadMgrWnd* task_wgt = new TaskWarheadMgrWnd(task_guid_, this);
		QDockWidget* dock_wgt = new QDockWidget;
		dock_wgt->setFloating(false);
		dock_wgt->setWidget(task_wgt);
		dock_wgt->setWindowTitle(task_wgt->windowTitle());
		addDockWidget(Qt::RightDockWidgetArea, dock_wgt);
		connect(task_wgt, SIGNAL(sig_current_warhead_changed(WarheadProperty*)), this, SLOT(on_set_current_warhead(WarheadProperty*)));

	}
	//动作-信号
	//connect(ui.actionNew, SIGNAL(triggered()), this, SLOT(on_new()));
	//connect(ui.actionSave, SIGNAL(triggered()), this, SLOT(on_save()));
	//connect(ui.actionSaveAs, SIGNAL(triggered()), this, SLOT(on_save_as()));
	//connect(ui.actionExport, SIGNAL(triggered()), this, SLOT(on_export()));
	//connect(ui.actionExportPower, SIGNAL(triggered()), this, SLOT(on_export_power()));
	//connect(ui.actionOpen, SIGNAL(triggered()), this, SLOT(on_open()));
	//connect(ui.actionImport, SIGNAL(triggered()), this, SLOT(on_import()));
	//connect(ui.actionMetal, SIGNAL(triggered()), this, SLOT(on_metal_material()));
	//connect(ui.actionCharge, SIGNAL(triggered()), this, SLOT(on_charge_material()));
	//connect(ui.actionProperty, SIGNAL(triggered()), this, SLOT(on_view_warhead_property()));
	//connect(ui.actionPower, SIGNAL(triggered()), this, SLOT(on_power_analysis()));
	//动作-激活状态
	//UpdateActionEnabled();
}
void DeseaWarheadMainCtrl::UpdateActionEnabled()
{
	ui.actionSave->setEnabled(warhead_);
	ui.actionSaveAs->setEnabled(warhead_ && GlobalTool::instance().IsWarheadExist(warhead_->get_guid()));
	ui.actionExport->setEnabled(warhead_);
	ui.actionExportPower->setEnabled(false);
	ui.actionProperty->setEnabled(warhead_);
	//ui.actionPower->setEnabled(warhead_ && warhead_->get_structure()->IsCompleteWarhaed());
}
//设置当前战斗部
void DeseaWarheadMainCtrl::on_set_current_warhead(WarheadProperty* warhead)
{
	warhead_draw_wnd_ = new WarheadDrawWnd(WarheadDrawWnd::kEdit, 0);
	mdi_area_->addSubWindow(warhead_draw_wnd_);
	//QMdiSubWindow* sub_wnd = warhead_2_doc_.value(warhead, 0);
	//if(!sub_wnd)
	//	sub_wnd = AddDoc(warhead);
	//mdi_area_->setActiveSubWindow(sub_wnd);
}
//新建战斗部
void DeseaWarheadMainCtrl::on_new()
{
	WarheadProperty* temp_warhead = warhead_;
	warhead_ = new WarheadProperty;
	WarheadPropertyDlg dlg(warhead_, WarheadPropertyDlg::kCreate, this);
	if(QDialog::Accepted == dlg.exec())
	{
		if(temp_warhead)
		{
			delete temp_warhead; 
		}
		WarheadModel* structure = warhead_->get_structure();
		Q_ASSERT(structure);
		warhead_draw_wnd_->set_model(structure);
		UpdateActionEnabled();
	}
}
//保存战斗部到数据库
void DeseaWarheadMainCtrl::on_save()
{
	if(warhead_)
	{
		bool ok = GlobalTool::instance().SaveWarhead(warhead_);
		if(!ok)
		{
			QMessageBox box;
			box.setIcon(QMessageBox::Critical);
			box.addButton(ExpandQtCore::fromGBK("确定"), QMessageBox::AcceptRole);
			box.setText(ExpandQtCore::fromGBK("保存战斗部失败！"));
			box.setWindowTitle(ExpandQtCore::fromGBK("错误"));
			box.exec();
			UpdateActionEnabled();
		}
	}
}
//另存战斗部到数据库
void DeseaWarheadMainCtrl::on_save_as(){}
//导出战斗部结构到文件
void DeseaWarheadMainCtrl::on_export(){}
//导出战斗部威力到文件
void DeseaWarheadMainCtrl::on_export_power(){}
//从数据库中选择一个战斗部打开
void DeseaWarheadMainCtrl::on_open()
{

}
//从数据库中打开指定战斗部
void DeseaWarheadMainCtrl::on_open(const QString& guid)
{

}
//从文件导入战斗部结构
void DeseaWarheadMainCtrl::on_import()
{
	QString file_name = QFileDialog::getOpenFileName(this, ExpandQtCore::fromGBK("打开"), 
		QString(), ExpandQtCore::fromGBK("战斗部模型 (*.whd)"));
	if(!file_name.isEmpty())
	{
		WarheadRead reader;
		WarheadModel* structure = reader.ReadXMLFile(file_name);
		if(structure)
		{
			if(warhead_) delete warhead_;
			warhead_ = new WarheadProperty;
			warhead_->set_structure(structure);
			warhead_draw_wnd_->set_model(structure);
			UpdateActionEnabled();
		}
	}
}
//查看金属材料
void DeseaWarheadMainCtrl::on_metal_material()
{
	MaterialViewDlg dlg(MaterialViewDlg::kMetal, this);
	dlg.exec();
}
//查看装药材料
void DeseaWarheadMainCtrl::on_charge_material()
{
	MaterialViewDlg dlg(MaterialViewDlg::kCharge, this);
	dlg.exec();
}
//查看战斗部属性
void DeseaWarheadMainCtrl::on_view_warhead_property()
{
	if(warhead_)
	{
		WarheadPropertyDlg dlg(warhead_, WarheadPropertyDlg::kAlter, this);
		dlg.exec();
	}
}

//威力分析
void DeseaWarheadMainCtrl::on_power_analysis()
{
	if(0 == warhead_)
	{
		ExpandQtGui::warning(this, ExpandQtCore::fromGBK("警告"), ExpandQtCore::fromGBK("请先新建或打开战斗部！"));
		return ;
	}
	if(!warhead_->get_structure()->IsCompleteWarhaed())
	{
		ExpandQtGui::warning(this, ExpandQtCore::fromGBK("警告"), ExpandQtCore::fromGBK("战斗部不完整，请确保已建立起爆点和装药段！"));
		return ;
	}
	PowerAnalysisWgt  w(ExpandQtCore::fromGBK("威力流程配置.xml"), ExpandQtCore::fromGBK("算法-字典-utf-8.xml"), warhead_->get_structure());
	w.exec();
}
///protected
void DeseaWarheadMainCtrl::closeEvent(QCloseEvent * event)
{
	//对每一个战斗部，检查并询问是否保存
	foreach(WarheadProperty* warhead, warhead_2_doc_.keys())
	{
		CheckAndAskSave(warhead);
	}
}

///private

//增加文档
QMdiSubWindow* DeseaWarheadMainCtrl::AddDoc(WarheadProperty* warhead)
{
	WarheadDrawWnd* draw_wnd = new WarheadDrawWnd(WarheadDrawWnd::kEdit, 0/*warhead->get_structure()*/);
	QMdiSubWindow* sub_wnd = mdi_area_->addSubWindow(draw_wnd);
	warhead_2_doc_.insert(warhead, sub_wnd);
	return sub_wnd;
}
//删除文档
QMdiSubWindow* DeseaWarheadMainCtrl::DeleteDoc(WarheadProperty* warhead)
{
	QMdiSubWindow* sub_wnd = warhead_2_doc_.value(warhead, 0);
	if(sub_wnd)
	{
		CheckAndAskSave(warhead);
		warhead_2_doc_.remove(warhead);
		mdi_area_->removeSubWindow(sub_wnd);
	}
	return sub_wnd;
}
//检查及询问是否保存
void DeseaWarheadMainCtrl::CheckAndAskSave(WarheadProperty* warhead)
{
	//判断是否已保存到数据库
	//若未保存，询问是否保存
	//若保存，判断是否已更新
	//若已更新，询问是否保存
}