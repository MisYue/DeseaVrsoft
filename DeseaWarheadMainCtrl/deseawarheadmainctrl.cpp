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
	//��ģģ��
	//warhead_draw_wnd_ = new WarheadDrawWnd(WarheadDrawWnd::kEdit, 0);
	//mdi_area_->addSubWindow(warhead_draw_wnd_);

	//layout->addWidget(warhead_draw_wnd_);
	//�����Ӧ��ս�����б�
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
	//����-�ź�
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
	//����-����״̬
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
//���õ�ǰս����
void DeseaWarheadMainCtrl::on_set_current_warhead(WarheadProperty* warhead)
{
	warhead_draw_wnd_ = new WarheadDrawWnd(WarheadDrawWnd::kEdit, 0);
	mdi_area_->addSubWindow(warhead_draw_wnd_);
	//QMdiSubWindow* sub_wnd = warhead_2_doc_.value(warhead, 0);
	//if(!sub_wnd)
	//	sub_wnd = AddDoc(warhead);
	//mdi_area_->setActiveSubWindow(sub_wnd);
}
//�½�ս����
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
//����ս���������ݿ�
void DeseaWarheadMainCtrl::on_save()
{
	if(warhead_)
	{
		bool ok = GlobalTool::instance().SaveWarhead(warhead_);
		if(!ok)
		{
			QMessageBox box;
			box.setIcon(QMessageBox::Critical);
			box.addButton(ExpandQtCore::fromGBK("ȷ��"), QMessageBox::AcceptRole);
			box.setText(ExpandQtCore::fromGBK("����ս����ʧ�ܣ�"));
			box.setWindowTitle(ExpandQtCore::fromGBK("����"));
			box.exec();
			UpdateActionEnabled();
		}
	}
}
//���ս���������ݿ�
void DeseaWarheadMainCtrl::on_save_as(){}
//����ս�����ṹ���ļ�
void DeseaWarheadMainCtrl::on_export(){}
//����ս�����������ļ�
void DeseaWarheadMainCtrl::on_export_power(){}
//�����ݿ���ѡ��һ��ս������
void DeseaWarheadMainCtrl::on_open()
{

}
//�����ݿ��д�ָ��ս����
void DeseaWarheadMainCtrl::on_open(const QString& guid)
{

}
//���ļ�����ս�����ṹ
void DeseaWarheadMainCtrl::on_import()
{
	QString file_name = QFileDialog::getOpenFileName(this, ExpandQtCore::fromGBK("��"), 
		QString(), ExpandQtCore::fromGBK("ս����ģ�� (*.whd)"));
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
//�鿴��������
void DeseaWarheadMainCtrl::on_metal_material()
{
	MaterialViewDlg dlg(MaterialViewDlg::kMetal, this);
	dlg.exec();
}
//�鿴װҩ����
void DeseaWarheadMainCtrl::on_charge_material()
{
	MaterialViewDlg dlg(MaterialViewDlg::kCharge, this);
	dlg.exec();
}
//�鿴ս��������
void DeseaWarheadMainCtrl::on_view_warhead_property()
{
	if(warhead_)
	{
		WarheadPropertyDlg dlg(warhead_, WarheadPropertyDlg::kAlter, this);
		dlg.exec();
	}
}

//��������
void DeseaWarheadMainCtrl::on_power_analysis()
{
	if(0 == warhead_)
	{
		ExpandQtGui::warning(this, ExpandQtCore::fromGBK("����"), ExpandQtCore::fromGBK("�����½����ս������"));
		return ;
	}
	if(!warhead_->get_structure()->IsCompleteWarhaed())
	{
		ExpandQtGui::warning(this, ExpandQtCore::fromGBK("����"), ExpandQtCore::fromGBK("ս��������������ȷ���ѽ����𱬵��װҩ�Σ�"));
		return ;
	}
	PowerAnalysisWgt  w(ExpandQtCore::fromGBK("������������.xml"), ExpandQtCore::fromGBK("�㷨-�ֵ�-utf-8.xml"), warhead_->get_structure());
	w.exec();
}
///protected
void DeseaWarheadMainCtrl::closeEvent(QCloseEvent * event)
{
	//��ÿһ��ս��������鲢ѯ���Ƿ񱣴�
	foreach(WarheadProperty* warhead, warhead_2_doc_.keys())
	{
		CheckAndAskSave(warhead);
	}
}

///private

//�����ĵ�
QMdiSubWindow* DeseaWarheadMainCtrl::AddDoc(WarheadProperty* warhead)
{
	WarheadDrawWnd* draw_wnd = new WarheadDrawWnd(WarheadDrawWnd::kEdit, 0/*warhead->get_structure()*/);
	QMdiSubWindow* sub_wnd = mdi_area_->addSubWindow(draw_wnd);
	warhead_2_doc_.insert(warhead, sub_wnd);
	return sub_wnd;
}
//ɾ���ĵ�
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
//��鼰ѯ���Ƿ񱣴�
void DeseaWarheadMainCtrl::CheckAndAskSave(WarheadProperty* warhead)
{
	//�ж��Ƿ��ѱ��浽���ݿ�
	//��δ���棬ѯ���Ƿ񱣴�
	//�����棬�ж��Ƿ��Ѹ���
	//���Ѹ��£�ѯ���Ƿ񱣴�
}