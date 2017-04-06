#pragma once
#include <QtWidgets>

//战斗部属性包装
class WarheadDataEntity;
struct WarheadPropertyWrap
{
	WarheadDataEntity* warhead;	//战斗部，初始化为NULL
	QString metal_source_file;	//金属材料来源，为空，从数据库获取材料
	QString charge_source_file;	//装药材料来源，为空，从数据库获取材料

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
		kCreate,	//创建
		kView,		//查看
		kAlter,		//修改
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
	// 创建材料库
	void CreateMaterialLib();
	// 获取单位
	int GetUnit(UnitType type);
	// 获取一级类别下的二级类别名称
	QStringList GetSubClassNames(const QString& class_guid);
	// 获取二级类别名称
	QString GetSubClassName(const QString& guid);
	// 获取二级类别GUID
	QString GetSubClassGuid(const QString& name);
	// 获取二级类别对应的一级类别名称
	QString GetClassName(const QString& sub_class_guid);
	// 是否已更改
	bool IsAltered();
	QMap<UnitType, QMap<int, QRadioButton*> > unit_radio_map_;
};

