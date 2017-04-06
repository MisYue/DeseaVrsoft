//ս���������ඨ���ļ�

#ifndef DESEAWARHEADMAINCTRL_H
#define DESEAWARHEADMAINCTRL_H

#include <QtWidgets>
#include "ui_deseawarheadmainctrl.h"

class DBConn;
class WarheadProperty;
class WarheadDrawWnd;

//���ĵ�ʵ�֣�֧��ͬʱ�򿪶��ս����
class DeseaWarheadMainCtrl : public QMainWindow
{
	Q_OBJECT
public:
	DeseaWarheadMainCtrl(DBConn* db_conn, const QString& task_guid = QString(), QWidget *parent = 0);
	~DeseaWarheadMainCtrl();
public slots:
	//�½�ս����
	void on_new();
	//����ս���������ݿ�
	void on_save();
	//���ս���������ݿ�
	void on_save_as();
	//����ս�����ṹ���ļ�
	void on_export();
	//����ս�����������ļ�
	void on_export_power();
	//�����ݿ���ѡ��һ��ս������
	void on_open();
	//�����ݿ��д�ָ��ս����
	void on_open(const QString& guid);
	//���ļ�����ս�����ṹ
	void on_import();
	//�鿴��������
	void on_metal_material();
	//�鿴װҩ����
	void on_charge_material();
	//�鿴ս��������
	void on_view_warhead_property();
	//��������
	void on_power_analysis();

	//���õ�ǰս����
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

	QMdiArea* mdi_area_;	//���ĵ�������
	QMap<WarheadProperty*, QMdiSubWindow*> warhead_2_doc_;	//key:ս�������� value:�ĵ�

	///////˽�г�Ա����////////
	void InitUi();
	void UpdateActionEnabled();

	//�����ĵ�
	QMdiSubWindow* AddDoc(WarheadProperty* warhead);
	//ɾ���ĵ�
	QMdiSubWindow* DeleteDoc(WarheadProperty* warhead);
	//��鼰ѯ���Ƿ񱣴�
	void CheckAndAskSave(WarheadProperty* warhead);
};

#endif // DESEAWARHEADMAINCTRL_H
