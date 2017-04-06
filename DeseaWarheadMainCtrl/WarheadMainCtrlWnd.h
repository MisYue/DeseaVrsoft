//***************************************
//	����ʱ��:	2017:3:14   14:13
//	�ļ�����: 	WarheadMainCtrlWnd.h
//	�ļ�����:	��Ⱥ��
//	
//	����˵��:	ս�������ؽ����ඨ��
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
	//���õ�ǰս����
	void on_set_current_warhead(WarheadPropertyWrap* warhead_wrap);
	// ���ĵ�����
	void on_doc_active(QMdiSubWindow* wnd);

	// �½�
	void on_new(void);
	// ��
	void on_open(void);
	// ����
	void on_import(void);
	// ����
	void on_export(void);
	// ����
	void on_save(void);
	// ���
	void on_save_as(void);
	// ɾ��
	void on_delete(void);
	// ��������
	void on_metal(void);
	// װҩ����
	void on_charge(void);
	// ����
	void on_property(void);
	// ��������
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

	// ��ʼ��
	void Init();
	// �����ĵ�
	QMdiSubWindow* AddDoc(WarheadPropertyWrap* warhead_wrap);
	// ɾ���ĵ�
	QMdiSubWindow* DeleteDoc(WarheadPropertyWrap* warhead_wrap);
	// ���¶���״̬
	void UpdateActions(void);
	// ѯ���Ƿ񱣴�
	void AskSave(WarheadPropertyWrap* warhead_wrap);
	// �Ƿ���Ҫ����
	bool IsNeededSave(WarheadPropertyWrap* warhead_wrap);
};

