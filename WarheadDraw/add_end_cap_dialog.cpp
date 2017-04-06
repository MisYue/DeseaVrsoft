#include "add_end_cap_dialog.h"
#include "ui_add_end_cap.h"
#include <WarheadModelData/WarheadModelWrap.h>
#include <MaterialLib/materiallib.h>

AddEndCapDialog::AddEndCapDialog(WarheadModelWrap* model_wrap, QWidget* parent)
	: QDialog(parent)
	, model_wrap_(model_wrap)
	, model_(model_wrap->get_structure())
	, ui_(new Ui::AddEndCap)
	, new_end_cap_(0)
{
	Q_ASSERT_X(model_ != 0, "AddEndCapDialog::AddEndCapDialog", "model == NULL");
	ui_->setupUi(this);

	const WarheadEndCap* left_end_cap = model_->get_left_end_cap();
	const WarheadEndCap* right_end_cap = model_->get_right_end_cap();

	//Q_ASSERT(left_end_cap==0 || right_end_cap==0);

	if(left_end_cap)
	{
		ui_->radioButton_left->setEnabled(false);
		ui_->radioButton_right->setChecked(true);
	}
	if(right_end_cap)
	{
		ui_->radioButton_right->setEnabled(false);
		ui_->radioButton_left->setChecked(true);
	}
	ui_->doubleSpinBox_length->setDecimals(model_wrap_->GetLengthPrecisionHint());
	ui_->doubleSpinBox_length->setSuffix(model_wrap_->GetLengthUnit());
	Bit_UnitSystem us = model_wrap_->get_structure()->get_cs().Get_UnitSystem();
	ui_->doubleSpinBox_length->setMinimum(1.0 / us.Get_LengthCoefficient());
	ui_->doubleSpinBox_length->setMaximum(INT_MAX);
	ui_->doubleSpinBox_length->setSingleStep(1.0 / us.Get_LengthCoefficient());
	ui_->doubleSpinBox_length->setValue(15 / us.Get_LengthCoefficient());

	//ÉèÖÃ²ÄÁÏ¿â
	material_guid_2_name_ = model_wrap_->get_metal_lib()->GetAllGuidAndNames();
	ui_->comboBox_material->addItems(material_guid_2_name_.values());
}
AddEndCapDialog::~AddEndCapDialog()
{
	delete ui_;
}

void AddEndCapDialog::accept()
{
	if(ui_->radioButton_left->isChecked())
	{
		model_->AddLeftEndCap(ui_->doubleSpinBox_length->value());
		new_end_cap_ = model_->get_left_end_cap();
	}
	else
	{
		model_->AddRightEndCap(ui_->doubleSpinBox_length->value());
		new_end_cap_ = model_->get_right_end_cap();
	}
	QString material_guid = material_guid_2_name_.key(ui_->comboBox_material->currentText());
	new_end_cap_->set_material(model_wrap_->get_metal_lib()->GetMaterial(material_guid));
	QDialog::accept();
}

EditEndCapDialog::EditEndCapDialog(WarheadModelWrap* model_wrap, WarheadEndCap* end_cap, QWidget* parent)
	: AddEndCapDialog(model_wrap, parent)
	, end_cap_(end_cap)
	, is_length_changed_(false)
{
	Q_ASSERT_X(end_cap != 0, "EditEndCapDialog::EditEndCapDialog", "end_cap == NULL");
	ui_->radioButton_left->hide();
	ui_->radioButton_right->hide();
	ui_->doubleSpinBox_length->setValue(end_cap->get_length());
	const Material* mtl = end_cap_->get_material();
	if(mtl)
		ui_->comboBox_material->setCurrentIndex(ui_->comboBox_material->findText(mtl->get_name()));
}
EditEndCapDialog::~EditEndCapDialog()
{

}

void EditEndCapDialog::accept()
{
	QString material_guid = material_guid_2_name_.key(ui_->comboBox_material->currentText());
	end_cap_->set_material(model_wrap_->get_metal_lib()->GetMaterial(material_guid));
	double length = ui_->doubleSpinBox_length->value();
	double current_length = end_cap_->get_length();
	if(current_length != length)
	{
		is_length_changed_ = true;
		double dx = length - current_length;
		model_->AdjustAfterNodePosX(end_cap_, dx);
		end_cap_->set_lenght(length);

	}
	QDialog::accept();
}