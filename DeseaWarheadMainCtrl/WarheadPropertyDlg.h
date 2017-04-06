#pragma once
#include <QtWidgets>

//ս�������԰�װ
class WarheadDataEntity;
struct WarheadPropertyWrap
{
	WarheadDataEntity* warhead;	//ս��������ʼ��ΪNULL
	QString metal_source_file;	//����������Դ��Ϊ�գ������ݿ��ȡ����
	QString charge_source_file;	//װҩ������Դ��Ϊ�գ������ݿ��ȡ����

	WarheadPropertyWrap();
};

namespace Ui { class WarheadProperty; }
class WarheadPropertyDlg :
	public QDialog
{
	Q_OBJECT
public:
	enum Mode
	{
		kCreate,	//����
		kView,		//�鿴
		kAlter,		//�޸�
	};
	WarheadPropertyDlg(WarheadPropertyWrap* warhead_wrap, Mode mode = kCreate, QWidget* parent=0);
	virtual ~WarheadPropertyDlg(void);
public slots:
	void on_apply();
	void accept();
	void on_set_material_file();
	void on_view_material();
	void on_warhead_class_changed(const QString& text);
protected:
	WarheadPropertyWrap* warhead_wrap_;
	Mode mode_;
	Ui::WarheadProperty* ui_;
	QMap<QString, QString> warhead_class_guid_2_name_;
	QMap<QString, QMap<QString, QString> > warhead_sub_class_guid_2_name_;
	QMap<QString, QString> task_guid_2_name_;
	enum UnitType
	{
		kLength,
		kMass,
		kTime,
	};
	void Init();
	void ShowProperty();
	void GetProperty();
	// �������Ͽ�
	void CreateMaterialLib();
	// ��ȡ��λ
	int GetUnit(UnitType type);
	// ��ȡһ������µĶ����������
	QStringList GetSubClassNames(const QString& class_guid);
	// ��ȡ�����������
	QString GetSubClassName(const QString& guid);
	// ��ȡ�������GUID
	QString GetSubClassGuid(const QString& name);
	// ��ȡ��������Ӧ��һ���������
	QString GetClassName(const QString& sub_class_guid);
	// �Ƿ��Ѹ���
	bool IsAltered();
	QMap<UnitType, QMap<int, QRadioButton*> > unit_radio_map_;
};

