#include "WarheadMainCtrlWnd.h"
#include "TaskWarheadMgrWnd.h"
#include "SingleWarheadWnd.h"
#include "WarheadPropertyDlg.h"
#include "MaterialViewDlg.h"
#include <WarheadDataEntity/warheaddataentity.h>
#include <BasicTool/expandqtcore.h>
#include <BasicTool/expandqtgui.h>
#include <BasicTool/EnumMgr.h>
#include <WarheadFileReadWrite/warheadfilereadwriteengine.h>
#include <PowerAnalysis/PowerAnalysisWgt.h>

WarheadMainCtrlWnd::WarheadMainCtrlWnd(const QString& task_guid, QWidget *parent)
	: mdi_area_(new QMdiArea)
	, task_wnd_(0)
	, task_guid_(task_guid)
	, QMainWindow(0)
{
	setWindowTitle(ExpandQtCore::fromGBK("战斗部主控"));
	setCentralWidget(mdi_area_);
	QBrush brush(QColor(68, 88, 124));
	mdi_area_->setBackground(brush);
	QToolBar* tool_bar(new QToolBar);
	addToolBar(tool_bar);
	action_new_ = ExpandQtGui::createAction(ExpandQtCore::fromGBK("新建"), this, SLOT(on_new()));
	action_open_ = ExpandQtGui::createAction(ExpandQtCore::fromGBK("打开"), this, SLOT(on_open()));
	action_import_ = ExpandQtGui::createAction(ExpandQtCore::fromGBK("导入"), this, SLOT(on_import()));
	action_save_ = ExpandQtGui::createAction(ExpandQtCore::fromGBK("保存"), this, SLOT(on_save()));
	action_save_as_ = ExpandQtGui::createAction(ExpandQtCore::fromGBK("另存"), this, SLOT(on_save_as()));
	action_export_ = ExpandQtGui::createAction(ExpandQtCore::fromGBK("导出"), this, SLOT(on_export()));
	action_delete_ = ExpandQtGui::createAction(ExpandQtCore::fromGBK("删除"), this, SLOT(on_delete()));
	action_property_ = ExpandQtGui::createAction(ExpandQtCore::fromGBK("属性"), this, SLOT(on_property()));
	action_metal_ = ExpandQtGui::createAction(ExpandQtCore::fromGBK("金属材料"), this, SLOT(on_metal()));
	action_charge_ = ExpandQtGui::createAction(ExpandQtCore::fromGBK("炸药材料"), this, SLOT(on_charge()));
	action_power_ = ExpandQtGui::createAction(ExpandQtCore::fromGBK("威力分析"), this, SLOT(on_power()));

	tool_bar->addAction(action_new_);
	tool_bar->addAction(action_open_);
	tool_bar->addAction(action_import_);
	tool_bar->addAction(action_export_);
	tool_bar->addAction(action_save_);
	tool_bar->addAction(action_save_as_);
	tool_bar->addAction(action_delete_);
	tool_bar->addAction(action_property_);
	tool_bar->addAction(action_metal_);
	tool_bar->addAction(action_charge_);
	tool_bar->addAction(action_power_);
	connect(mdi_area_, SIGNAL(subWindowActivated(QMdiSubWindow*)), this, SLOT(on_doc_active(QMdiSubWindow*)));
	Init();
}


WarheadMainCtrlWnd::~WarheadMainCtrlWnd(void)
{
}

///slots

// 新建
void WarheadMainCtrlWnd::on_new(void)
{
	WarheadPropertyWrap* warhead_wrap = new WarheadPropertyWrap;
	warhead_wrap->warhead = new WarheadDataEntity;
	WarheadPropertyDlg dlg(warhead_wrap, WarheadPropertyDlg::kCreate, this);
	if(QDialog::Accepted == dlg.exec())
	{
		AddDoc(warhead_wrap);
		warhead_wrap_owned_.append(warhead_wrap);
	}
	else
	{
		delete warhead_wrap->warhead;
		delete warhead_wrap;
	}
}

// 打开
void WarheadMainCtrlWnd::on_open(void)
{
}


// 导入
void WarheadMainCtrlWnd::on_import(void)
{
	QString file_name = QFileDialog::getOpenFileName(this, ExpandQtCore::fromGBK("打开"), QString(), ExpandQtCore::fromGBK("战斗部模型 (*.whd)"));
	if(!file_name.isEmpty())
	{
		WarheadFileReadWriteEngine reader;
		WarheadDataEntity* warhead = reader.Read(file_name);
		if(!warhead)
		{
			ExpandQtGui::critical(this, ExpandQtCore::fromGBK("错误"), ExpandQtCore::fromGBK("打开失败！"));
			return;
		}
		WarheadPropertyWrap* warhead_wrap = new WarheadPropertyWrap;
		warhead_wrap->warhead = warhead;
		AddDoc(warhead_wrap);
		warhead_wrap_owned_.append(warhead_wrap);
	}
}


// 导出
void WarheadMainCtrlWnd::on_export(void)
{
	//获取当前活动战斗部
	QMdiSubWindow* sub_wnd = mdi_area_->activeSubWindow();
	if(sub_wnd)
	{
		WarheadPropertyWrap* warhead_wrap = warhead_2_sub_wnd_.key(sub_wnd, 0);
		if(warhead_wrap)
		{
			EnumMgr& enum_mgr = EnumMgr::instance();
			QStringList export_formats = enum_mgr.GetNames<WarheadFileReadWriteEngine::Format>();
			QStringList export_selected_formats;
			ExpandQtGui::selectDlg(export_formats, export_selected_formats, this);
			if(!export_selected_formats.isEmpty())
			{
				QString file_name = QFileDialog::getSaveFileName(this, ExpandQtCore::fromGBK("保存"), QString());
				if(!file_name.isEmpty())
				{
					WarheadReadWriteWrap read_write_wrap;
					read_write_wrap.warhead = warhead_wrap->warhead;
					SingleWarheadWnd* warhead_wnd = qobject_cast<SingleWarheadWnd*>(sub_wnd->widget());
					read_write_wrap.painter_2d = warhead_wnd->GetPainter2D();
					read_write_wrap.painter_3d = warhead_wnd->GetPainter3D();
					WarheadFileReadWriteEngine writer;
					foreach(const QString& format, export_selected_formats)
					{
						if(!writer.Write(&read_write_wrap, file_name+"."+format))
							ExpandQtGui::critical(this, ExpandQtCore::fromGBK("错误"), ExpandQtCore::fromGBK("导出失败"));
					}
				}
			}
		}
	}
}


// 保存
void WarheadMainCtrlWnd::on_save(void)
{
}


// 另存
void WarheadMainCtrlWnd::on_save_as(void)
{
}

// 删除
void WarheadMainCtrlWnd::on_delete(void)
{

}

// 金属材料
void WarheadMainCtrlWnd::on_metal(void)
{
	//获取当前活动战斗部
	QMdiSubWindow* sub_wnd = mdi_area_->activeSubWindow();
	if(sub_wnd)
	{
		WarheadPropertyWrap* warhead_wrap = warhead_2_sub_wnd_.key(sub_wnd, 0);
		if(warhead_wrap)
		{
			MaterialViewDlg dlg(warhead_wrap->warhead->get_structure()->get_metal_lib(), this);
			dlg.setWindowTitle(ExpandQtCore::fromGBK("金属材料库"));
			dlg.exec();
		}
	}
}


// 装药材料
void WarheadMainCtrlWnd::on_charge(void)
{
	//获取当前活动战斗部
	QMdiSubWindow* sub_wnd = mdi_area_->activeSubWindow();
	if(sub_wnd)
	{
		WarheadPropertyWrap* warhead_wrap = warhead_2_sub_wnd_.key(sub_wnd, 0);
		if(warhead_wrap)
		{
			MaterialViewDlg dlg(warhead_wrap->warhead->get_structure()->get_charge_lib(), this);
			dlg.setWindowTitle(ExpandQtCore::fromGBK("装药材料库"));
			dlg.exec();
		}
	}
}


// 属性
void WarheadMainCtrlWnd::on_property(void)
{
	//获取当前活动战斗部
	QMdiSubWindow* sub_wnd = mdi_area_->activeSubWindow();
	if(sub_wnd)
	{
		WarheadPropertyWrap* warhead_wrap = warhead_2_sub_wnd_.key(sub_wnd, 0);
		if(warhead_wrap)
		{
			QString old_name = warhead_wrap->warhead->get_extra_property()->get_name();
			WarheadPropertyDlg dlg(warhead_wrap, WarheadPropertyDlg::kAlter, this);
			dlg.setWindowTitle(ExpandQtCore::fromGBK("模型属性"));
			dlg.exec();
			QString new_name = warhead_wrap->warhead->get_extra_property()->get_name();
			if(old_name != new_name)
			{
				sub_wnd->setWindowTitle(new_name);
				if(task_wnd_)
					task_wnd_->on_warhead_name_changed(warhead_wrap);
			}
		}
	}
}
// 威力分析
void WarheadMainCtrlWnd::on_power()
{
	//获取当前活动战斗部
	QMdiSubWindow* sub_wnd = mdi_area_->activeSubWindow();
	if(sub_wnd)
	{
		WarheadPropertyWrap* warhead_wrap = warhead_2_sub_wnd_.key(sub_wnd, 0);
		if(warhead_wrap)
		{
			PowerAnalysisWgt  w(ExpandQtCore::fromGBK("威力流程配置.xml"), ExpandQtCore::fromGBK("算法-字典-utf-8.xml"), warhead_wrap->warhead->get_structure());
			w.exec();
		}
	}
}

//设置当前战斗部
void WarheadMainCtrlWnd::on_set_current_warhead(WarheadPropertyWrap* warhead_wrap)
{
	QMdiSubWindow* sub_wnd = warhead_2_sub_wnd_.value(warhead_wrap, 0);
	if(!sub_wnd)
		sub_wnd = AddDoc(warhead_wrap);
	if(mdi_area_->activeSubWindow() != sub_wnd)
		mdi_area_->setActiveSubWindow(sub_wnd);
}
// 子文档激活
void WarheadMainCtrlWnd::on_doc_active(QMdiSubWindow* wnd)
{
	if(wnd)
	{
		SingleWarheadWnd* warhead_wnd = qobject_cast<SingleWarheadWnd*>(wnd->widget());
		UpdateActions();
	}
}
///protected
// 初始化
void WarheadMainCtrlWnd::Init()
{
	//创建任务管理界面
	if(!task_guid_.isEmpty())
	{
		task_wnd_ = new TaskWarheadMgrWnd(task_guid_, this);
		QDockWidget* dock_wgt = new QDockWidget;
		dock_wgt->setFloating(false);
		dock_wgt->setWidget(task_wnd_);
		dock_wgt->setWindowTitle(task_wnd_->windowTitle());
		addDockWidget(Qt::RightDockWidgetArea, dock_wgt);
		connect(task_wnd_, SIGNAL(sig_current_warhead_changed(WarheadPropertyWrap*)), this, SLOT(on_set_current_warhead(WarheadPropertyWrap*)));
		task_wnd_->Init();
	}
	else
	{
		action_open_->setEnabled(false);
		action_save_->setEnabled(false);
		action_save_as_->setEnabled(false);
		action_delete_->setEnabled(false);
	}
}
// 增加文档
QMdiSubWindow* WarheadMainCtrlWnd::AddDoc(WarheadPropertyWrap* warhead_wrap)
{
	SingleWarheadWnd* warhead_wnd = new SingleWarheadWnd(warhead_wrap);
	QMdiSubWindow* sub_wnd = mdi_area_->addSubWindow(warhead_wnd);
	sub_wnd->setWindowTitle(warhead_wrap->warhead->get_extra_property()->get_name());
	sub_wnd->showMaximized();
	warhead_2_sub_wnd_.insert(warhead_wrap, sub_wnd);
	return sub_wnd;
}
// 删除文档
QMdiSubWindow* WarheadMainCtrlWnd::DeleteDoc(WarheadPropertyWrap* warhead_wrap)
{
	QMdiSubWindow* sub_wnd = warhead_2_sub_wnd_.value(warhead_wrap, 0);
	if(sub_wnd)
	{
		warhead_2_sub_wnd_.remove(warhead_wrap);
		mdi_area_->removeSubWindow(sub_wnd);
	}
	return sub_wnd;
}

// 更新动作状态
void WarheadMainCtrlWnd::UpdateActions(void)
{
}


// 询问是否保存
void WarheadMainCtrlWnd::AskSave(WarheadPropertyWrap* warhead_wrap)
{
}


// 是否需要保存
bool WarheadMainCtrlWnd::IsNeededSave(WarheadPropertyWrap* warhead_wrap)
{
	return false;
}
