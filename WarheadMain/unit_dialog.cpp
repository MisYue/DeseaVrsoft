#include "unit_dialog.h"
#include "ui_unit.h"
#include "material_dialog.h"
#include <tool/global_data.h>
#include <tool/tool.h>
#include <WarheadMaterialLib/warheadmateriallib.h>

QString g_cfg = "vm.cfg";

UnitDialog::UnitDialog(QWidget* parent)
	: ui_(new Ui::unit)
	, metal_already_open_(false)
	, charge_already_open_(false)
	, QDialog(parent)
{
	ui_->setupUi(this);
	GlobalData& global_data = GlobalData::instance();
	ui_->groupBox_length->setLayout(CreateLayout(global_data.GetLengthUnitNames(), global_data.GetLengthUnit()));
	ui_->groupBox_mass->setLayout(CreateLayout(global_data.GetMassUnitNames(), global_data.GetMassUnit()));
	ui_->groupBox_time->setLayout(CreateLayout(global_data.GetTimeUnitNames(), global_data.GetTimeUnit()));


	connect(ui_->pushButton_metal, SIGNAL(clicked()), this, SLOT(on_set_material_file()));
	connect(ui_->pushButton_charge, SIGNAL(clicked()), this, SLOT(on_set_material_file()));
	connect(ui_->lineEdit_metal, SIGNAL(textChanged(const QString&)), this, SLOT(on_material_file_changed(const QString&)));
	connect(ui_->lineEdit__charge, SIGNAL(textChanged(const QString&)), this, SLOT(on_material_file_changed(const QString&)));
	connect(ui_->pushButton_charge_view, SIGNAL(clicked()), this, SLOT(on_view_material()));
	connect(ui_->pushButton_metal_view, SIGNAL(clicked()), this, SLOT(on_view_material()));


	//读取材料文件的设置信息
	QSettings set(g_cfg, QSettings::IniFormat);
	QString metal_file = set.value("metal_file").toString();
	QString charge_file = set.value("charge_file").toString();
	ui_->lineEdit_metal->setText(metal_file);
	ui_->lineEdit__charge->setText(charge_file);
}
UnitDialog::~UnitDialog()
{
	delete ui_;
}

void UnitDialog::accept()
{
	QString length = GetCurrentUnit(ui_->groupBox_length->layout());
	QString mass = GetCurrentUnit(ui_->groupBox_mass->layout());
	QString time = GetCurrentUnit(ui_->groupBox_time->layout());
	GlobalData::instance().set_unit_system(length, mass, time);

	QString metal_file = ui_->lineEdit_metal->text();
	QString charge_file = ui_->lineEdit__charge->text();

	if(!metal_already_open_)
		WarheadMaterialLib::intances().ReadMetals(metal_file);
	if(!charge_already_open_)
		WarheadMaterialLib::intances().ReadCharges(charge_file);

	//保存材料文件的设置信息
	QSettings set(g_cfg, QSettings::IniFormat);
	set.setValue("metal_file", metal_file);
	set.setValue("charge_file", charge_file);

	QDialog::accept();
}
void UnitDialog::on_set_material_file()
{
	QObject* from = sender();
	if(from == ui_->pushButton_metal)
		ui_->lineEdit_metal->setText(QFileDialog::getOpenFileName(this, GBK2Unicode("材料文件"), QApplication::applicationDirPath(), GBK2Unicode("材料 (*.csv *.txt)")));
	else if(from == ui_->pushButton_charge)
		ui_->lineEdit__charge->setText(QFileDialog::getOpenFileName(this, GBK2Unicode("材料文件"), QApplication::applicationDirPath(), GBK2Unicode("材料 (*.csv *.txt)")));
}
QLayout* UnitDialog::CreateLayout(const QStringList& unit_names, const QString& current_unit)
{
	QHBoxLayout* layout = new QHBoxLayout;
	foreach(const QString& name, unit_names)
	{
		QRadioButton* button = new QRadioButton(name, this);
		layout->addWidget(button);
		if(current_unit == name)
			button->setChecked(true);
	}
	layout->addSpacerItem(new QSpacerItem(40, 20, QSizePolicy::Expanding));
	return layout;
}
QString UnitDialog::GetCurrentUnit(QLayout* layout)
{
	int count = layout->count();
	for(int i=0; i<count; ++i)
	{
		QLayoutItem* item = layout->itemAt(i);
		QWidgetItem* widget_item = dynamic_cast<QWidgetItem*>(item);
		if(widget_item)
		{
			QRadioButton* button = dynamic_cast<QRadioButton*>(widget_item->widget());
			if(button && button->isChecked())
				return button->text();
		}
	}
	return QString();
}

void UnitDialog::on_material_file_changed(const QString& text)
{
	if(ui_->lineEdit_metal == sender())
		metal_already_open_ = false;
	else
		charge_already_open_ = false;
}
void UnitDialog::on_view_material()
{
	MaterialDialog::Type type;
	if(ui_->pushButton_metal_view == sender())
	{
		metal_already_open_ = true;
		type = MaterialDialog::kMetal;
		WarheadMaterialLib::intances().ReadMetals(ui_->lineEdit_metal->text());
	}
	else
	{
		charge_already_open_ = true;
		type = MaterialDialog::kCharge;
		WarheadMaterialLib::intances().ReadCharges(ui_->lineEdit__charge->text());
	}
	MaterialDialog dialog(type, this);
	dialog.resize(800, 600);
	dialog.exec();
}

