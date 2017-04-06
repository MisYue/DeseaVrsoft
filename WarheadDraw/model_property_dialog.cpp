#include "model_property_dialog.h"
#include "ui_model_property.h"
#include <WarheadModelData/WarheadModelWrap.h>
#include <BasicTool/expandqtcore.h>

ModelPropertyDialog::ModelPropertyDialog(WarheadModelWrap* model_wrap, QWidget* parent)
	: QDialog(parent)
	, model_wrap_(model_wrap)
	, model_(model_wrap->get_structure())
	, ui_(new Ui::ModelProperty)
	, is_name_changed_(false)
{
	ui_->setupUi(this);
	Q_ASSERT_X(model_ != 0, "ModelPropertyDialog::ModelPropertyDialog", "model == NULL");
	//int precision_hint = GlobalData::instance().GetLengthPrecisionHint();
	ui_->doubleSpinBox_length->setSuffix(model_wrap_->GetLengthUnit());
	ui_->doubleSpinBox_mass->setSuffix(model_wrap_->GetMassUnit());
	ui_->doubleSpinBox_shell_mass->setSuffix(model_wrap_->GetMassUnit());
	ui_->doubleSpinBox_charge_mass->setSuffix(model_wrap_->GetMassUnit());
	ui_->comboBox_type->addItems(QStringList() << ExpandQtCore::fromGBK("É±±¬µ¯") << ExpandQtCore::fromGBK("ÇÖ±¬µ¯"));
	ui_->lineEdit_name->setText(model_->get_name());
	ui_->comboBox_type->setCurrentIndex(model_->get_type());
	ui_->comboBox_type->setEnabled(false);

	//ui_->doubleSpinBox_length->setDecimals(precision_hint);



	model_->UpdateCharacterData();
	const WarheadCharacterData& character_data = model_->get_character_data();
	ui_->doubleSpinBox_length->setValue(character_data.length);
	ui_->doubleSpinBox_mass->setValue(character_data.mass);
	ui_->doubleSpinBox_charge_mass->setValue(character_data.charge_mass);
	ui_->doubleSpinBox_shell_mass->setValue(character_data.shell_mass);
}

ModelPropertyDialog::~ModelPropertyDialog()
{
	delete ui_;
}

void ModelPropertyDialog::accept()
{
	QString name = ui_->lineEdit_name->text();
	if(name != model_->get_name())
	{
		model_->set_name(name);
		is_name_changed_ = true;
	}
	model_->set_type(static_cast<WarheadType>(ui_->comboBox_type->currentIndex()));
	QDialog::accept();
}