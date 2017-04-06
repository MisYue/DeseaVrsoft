#include "WarheadPropertyDlg.h"
#include "ui_warheadproperty.h"
#include "MaterialViewDlg.h"
#include "GlobalDataWrap.h"
#include <WarheadDataEntity/warheaddataentity.h>
#include <MaterialLib/MetalLib.h>
#include <MaterialLib/ChargeLib.h>
#include <BasicTool/expandqtcore.h>
#include <TaskDBAccess/taskdbaccess.h>
#include <WarheadDBAccess/warheaddbaccess.h>


WarheadPropertyWrap::WarheadPropertyWrap() : warhead(0) {}

WarheadPropertyDlg::WarheadPropertyDlg(WarheadPropertyWrap* warhead_wrap, Mode mode, QWidget* parent)
	: QDialog(parent)
	, warhead_wrap_(warhead_wrap)
	, mode_(mode)
	, ui_(new Ui::WarheadProperty)
{
	Q_ASSERT(warhead_wrap);
	ui_->setupUi(this);
	Init();
}
WarheadPropertyDlg::~WarheadPropertyDlg(void)
{
	delete ui_;
}

void WarheadPropertyDlg::on_set_material_file()
{
	QObject* from = sender();
	if(from == ui_->pushButton_metal)
	{
		ui_->lineEdit_metal->setText(QFileDialog::getOpenFileName(this, ExpandQtCore::fromGBK("材料文件"), QApplication::applicationDirPath(), ExpandQtCore::fromGBK("材料 (*.csv *.txt)")));
	}
	else if(from == ui_->pushButton_charge)
	{
		ui_->lineEdit_charge->setText(QFileDialog::getOpenFileName(this, ExpandQtCore::fromGBK("材料文件"), QApplication::applicationDirPath(), ExpandQtCore::fromGBK("材料 (*.csv *.txt)")));
	}
}

void WarheadPropertyDlg::on_view_material()
{
	MaterialLib* material_lib = 0;
	CreateMaterialLib();
	QString title;
	if(ui_->pushButton_metal_view == sender())
	{
		material_lib = warhead_wrap_->warhead->get_structure()->get_metal_lib();
		title = ExpandQtCore::fromGBK("金属材料库");
	}
	else
	{
		material_lib = warhead_wrap_->warhead->get_structure()->get_charge_lib();
		title = ExpandQtCore::fromGBK("装药材料库");
	}
	MaterialViewDlg dialog(material_lib, this);
	dialog.setWindowTitle(title);
	dialog.resize(800, 600);
	dialog.exec();
}
void WarheadPropertyDlg::on_warhead_class_changed(const QString& text)
{
	QString class_guid = warhead_class_guid_2_name_.key(text, QString());
	QStringList sub_class_names = GetSubClassNames(class_guid);
	ui_->comboBox_sub_class_name->clear();
	ui_->comboBox_sub_class_name->addItems(sub_class_names);
}
void WarheadPropertyDlg::on_apply()
{
	switch(mode_)
	{
	case kAlter:
		if(IsAltered())
		{
			GetProperty();
			//更新修改时间
			WarheadExtraProperty* prop = warhead_wrap_->warhead->get_extra_property();
			prop->set_update_time(QDateTime::currentDateTime());
		}
		break;
	case kCreate:
		GetProperty();
		break;
	}
}
void WarheadPropertyDlg::accept()
{
	switch(mode_)
	{
	case kAlter:
		if(IsAltered())
		{
			GetProperty();
			//更新修改时间
			WarheadExtraProperty* prop = warhead_wrap_->warhead->get_extra_property();
			prop->set_update_time(QDateTime::currentDateTime());
		}
		break;
	case kCreate:
		GetProperty();
		break;
	}
	QDialog::accept();
}
void WarheadPropertyDlg::Init()
{
	ui_->pushButtonApply->setEnabled(kView != mode_);
	connect(ui_->pushButton_metal, SIGNAL(clicked()), this, SLOT(on_set_material_file()));
	connect(ui_->pushButton_charge, SIGNAL(clicked()), this, SLOT(on_set_material_file()));

	connect(ui_->pushButton_charge_view, SIGNAL(clicked()), this, SLOT(on_view_material()));
	connect(ui_->pushButton_metal_view, SIGNAL(clicked()), this, SLOT(on_view_material()));
	// 用于显示与获取单位的相关结构初始化
	// 长度单位
	QMap<int, QRadioButton*>& length_value_2_radio_ = unit_radio_map_[kLength];
	length_value_2_radio_.insert(1, ui_->radioButton_mm); //mm
	length_value_2_radio_.insert(2, ui_->radioButton_cm); //cm
	length_value_2_radio_.insert(3, ui_->radioButton_m); //m
	length_value_2_radio_.insert(4, ui_->radioButton_km); //km
	// 质量单位
	QMap<int, QRadioButton*>& mass_value_2_radio_ = unit_radio_map_[kMass];
	mass_value_2_radio_.insert(1, ui_->radioButton_g); //g
	mass_value_2_radio_.insert(2, ui_->radioButton_kg); //kg
	// 时间单位
	QMap<int, QRadioButton*>& time_value_2_radio_ = unit_radio_map_[kTime];
	time_value_2_radio_.insert(1, ui_->radioButton_us); //us
	time_value_2_radio_.insert(2, ui_->radioButton_ms); //ms
	time_value_2_radio_.insert(3, ui_->radioButton_s); //s

	switch(mode_)
	{
	case kView:
		{
			// 禁用所有编辑项，只可查看属性及材料库
			// 单位与材料页
			ui_->groupBox_unit_length->setEnabled(false);
			ui_->groupBox_unit_mass->setEnabled(false);
			ui_->groupBox_unit_time->setEnabled(false);
			ui_->lineEdit_metal->setEnabled(false);
			ui_->lineEdit_charge->setEnabled(false);
			ui_->pushButton_metal->setEnabled(false);
			ui_->pushButton_charge->setEnabled(false);
			// 基本属性页
			ui_->tab_2->setEnabled(false);
		}
	case kAlter:
		{
			// 禁用单位与材料页编辑项
			ui_->groupBox_unit_length->setEnabled(false);
			ui_->groupBox_unit_mass->setEnabled(false);
			ui_->groupBox_unit_time->setEnabled(false);
			ui_->lineEdit_metal->setEnabled(false);
			ui_->lineEdit_charge->setEnabled(false);
			ui_->pushButton_metal->setEnabled(false);
			ui_->pushButton_charge->setEnabled(false);
			// 禁用基本属性页的一级类别和二级类别
			ui_->comboBox_class_name->setEnabled(false);
			ui_->comboBox_sub_class_name->setEnabled(false);
		}
		break;
	case kCreate:
		{
			connect(ui_->comboBox_class_name, SIGNAL(currentIndexChanged(const QString&)), this, SLOT(on_warhead_class_changed(const QString&)));
			// 任务
			DBConn* db_conn = GlobalDataWrap::instance().get_db_conn();
			TaskDBAccess task_db(db_conn);
			task_db.GetGuidAndNames(task_guid_2_name_);
			ui_->comboBox_task_name->addItems(task_guid_2_name_.values());
			// 类别
			WarheadDBAccess warhead_db(db_conn);
			warhead_db.GetClassGuidAndNames(warhead_class_guid_2_name_);
			ui_->comboBox_class_name->addItems(warhead_class_guid_2_name_.values());
		}
		break;
	}
	ShowProperty();
}

void WarheadPropertyDlg::ShowProperty()
{
	WarheadStructure* structure = warhead_wrap_->warhead->get_structure();
	WarheadModel* model = structure->get_structure();
	// 单位与材料页属性设置
	Bit_UnitSystem us = model->get_cs().Get_UnitSystem();
	// 长度单位
	int unit_length = us.Get_LengthUnit();
	unit_radio_map_[kLength].value(unit_length)->setChecked(true);
	// 质量单位
	int unit_mass = us.Get_MassUnit();
	unit_radio_map_[kMass].value(unit_mass)->setChecked(true);
	// 时间单位
	int unit_time = us.Get_TimeUnit();
	unit_radio_map_[kTime].value(unit_time)->setChecked(true);
	// 金属材料文件
	ui_->lineEdit_metal->setText(warhead_wrap_->metal_source_file);
	// 炸药材料文件
	ui_->lineEdit_charge->setText(warhead_wrap_->charge_source_file);

	// 基本属性页属性设置
	WarheadExtraProperty* prop = warhead_wrap_->warhead->get_extra_property();
	if(kCreate == mode_)
	{
		DBConn* db_conn = GlobalDataWrap::instance().get_db_conn();
		WarheadDBAccess warhead_db(db_conn);
		prop->set_id(warhead_db.GetNewId());
	}
	ui_->lineEdit_id->setText(QString::number(prop->get_id()));	//id
	ui_->lineEdit_guid->setText(prop->get_guid());	//guid
	ui_->lineEdit_name->setText(prop->get_name());	//name
	if(mode_!=kCreate)
	{
		QString sub_class_guid = prop->get_sub_class_guid();
		ui_->comboBox_sub_class_name->addItem(GetSubClassName(sub_class_guid));
		ui_->comboBox_class_name->addItem(GetClassName(sub_class_guid));
		ui_->comboBox_sub_class_name->setEnabled(false);
		ui_->comboBox_class_name->setEnabled(false);
	}

	ui_->comboBox_task_name->addItem(task_guid_2_name_.value(prop->get_task_guid()));	//任务
	ui_->comboBox_country->setCurrentText(prop->get_country()); //国家
	ui_->lineEdit_missile_name->setText(prop->get_missile_name());	//所配导弹
	ui_->checkBox_share->setChecked(prop->get_share());	//是否共享
	ui_->dateEdit_service_start->setDate(prop->get_service_start_date()); //服役时间
	ui_->dateEdit_service_end->setDate(prop->get_service_end_date()); //服役结束时间
	ui_->dateTimeEdit_create->setDateTime(prop->get_create_time()); //创建时间
	ui_->dateTimeEdit_update->setDateTime(prop->get_update_time()); //修改时间
	ui_->plainTextEdit_describe->setPlainText(prop->get_describe()); //描述
}
void WarheadPropertyDlg::GetProperty()
{
	WarheadStructure* structure = warhead_wrap_->warhead->get_structure();
	WarheadExtraProperty* prop = warhead_wrap_->warhead->get_extra_property();
	switch(mode_)
	{
	case kView:
		break;
	case kCreate:
		{
			// 单位制
			Bit_UnitSystem us(GetUnit(kLength), GetUnit(kMass), GetUnit(kTime));
			Bit_2DCSWithExpAndUS& cs = structure->get_structure()->get_cs();
			cs.Set_Initial(cs.Get_2DCSWithExplain(), us);
			// 材料
			CreateMaterialLib();
			// 二级类别
			prop->set_sub_class_guid(GetSubClassGuid(ui_->comboBox_sub_class_name->currentText()));
		}
	case kAlter:
		{
			prop->set_name(ui_->lineEdit_name->text()); //名称
			prop->set_country(ui_->comboBox_country->currentText()); //国家
			prop->set_missile_name(ui_->lineEdit_missile_name->text()); //所配导弹
			prop->set_share(ui_->checkBox_share->isChecked()); //是否共享
			prop->set_service_start_date(ui_->dateEdit_service_start->date()); //服役时间
			prop->set_service_end_date(ui_->dateEdit_service_end->date()); //服役结束时间
			prop->set_describe(ui_->plainTextEdit_describe->toPlainText()); //描述
		}
		break;
	}
}
// 创建材料库
void WarheadPropertyDlg::CreateMaterialLib()
{
	MaterialLib* material_lib = 0;
	{
		material_lib = warhead_wrap_->warhead->get_structure()->get_metal_lib();
		if(warhead_wrap_->metal_source_file != ui_->lineEdit_metal->text())
		{
			warhead_wrap_->metal_source_file = ui_->lineEdit_metal->text();
			material_lib->Init(warhead_wrap_->metal_source_file);
		}
	}
	{
		material_lib = warhead_wrap_->warhead->get_structure()->get_charge_lib();
		if(warhead_wrap_->charge_source_file != ui_->lineEdit_charge->text())
		{
			warhead_wrap_->charge_source_file = ui_->lineEdit_charge->text();
			material_lib->Init(warhead_wrap_->charge_source_file);
		}
	}
}
// 获取单位
int WarheadPropertyDlg::GetUnit(UnitType type)
{
	QMap<int, QRadioButton*>& unit_value_2_radio_ = unit_radio_map_[type];
	for(QMap<int, QRadioButton*>::iterator beg = unit_value_2_radio_.begin();
		beg != unit_value_2_radio_.end();
		++beg)
	{
		if(beg.value()->isChecked())
			return beg.key();
	}
	return 1;
}
// 获取一级类别下的二级类别名称
QStringList WarheadPropertyDlg::GetSubClassNames(const QString& class_guid)
{
	// 现在本地查，没有则查询数据库
	QMap<QString, QString> sub_class_guid_2_name = warhead_sub_class_guid_2_name_.value(class_guid);
	if(sub_class_guid_2_name.size()==0)
	{
		DBConn* db_conn = GlobalDataWrap::instance().get_db_conn();
		WarheadDBAccess warhead_db(db_conn);
		warhead_db.GetSubClassGuidAndNames(class_guid, sub_class_guid_2_name);
		warhead_sub_class_guid_2_name_[class_guid] = sub_class_guid_2_name;
	}
	return sub_class_guid_2_name.values();
}

// 获取二级类别名称
QString WarheadPropertyDlg::GetSubClassName(const QString& guid)
{
	DBConn* db_conn = GlobalDataWrap::instance().get_db_conn();
	WarheadDBAccess warhead_db(db_conn);
	return warhead_db.GetSubClassName(guid);
}
// 获取二级类别GUID
QString WarheadPropertyDlg::GetSubClassGuid(const QString& name)
{
	DBConn* db_conn = GlobalDataWrap::instance().get_db_conn();
	WarheadDBAccess warhead_db(db_conn);
	return warhead_db.GetSubClassGuid(name);
}
// 获取二级类别对应的一级类别名称
QString WarheadPropertyDlg::GetClassName(const QString& sub_class_guid)
{
	DBConn* db_conn = GlobalDataWrap::instance().get_db_conn();
	WarheadDBAccess warhead_db(db_conn);
	QString class_guid, class_name;
	warhead_db.GetClassGuidAndName(sub_class_guid, class_guid, class_name);
	return class_name;
}

// 是否已更改
bool WarheadPropertyDlg::IsAltered()
{
	WarheadExtraProperty* prop = warhead_wrap_->warhead->get_extra_property();
	if(kAlter == mode_)
	{
		if(prop->get_name() != ui_->lineEdit_name->text()) return true; //名称
		if(prop->get_country() != ui_->comboBox_country->currentText()) return true; //国家
		if(prop->get_missile_name() != ui_->lineEdit_missile_name->text()) return true; //所配导弹
		if(prop->get_share() != ui_->checkBox_share->isChecked()) return true; //是否共享
		if(prop->get_service_start_date() != ui_->dateEdit_service_start->date()) return true; //服役时间
		if(prop->get_service_end_date() != ui_->dateEdit_service_end->date()) return true; //服役结束时间
		if(prop->get_describe() != ui_->plainTextEdit_describe->toPlainText()) return true; //描述
	}
	return false;
}