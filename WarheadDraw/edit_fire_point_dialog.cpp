#include "edit_fire_point_dialog.h"
#include "ui_edit_fire_point.h"
#include <WarheadModelData/WarheadModelWrap.h>
#include <WarheadModelData/warhead_model.h>


EditFirePointDialog::EditFirePointDialog(WarheadModelWrap* model_wrap, WarheadFirePoint* fire_point, QWidget* parent)
	: QDialog(parent)
	, model_wrap_(model_wrap)
	, fire_point_(fire_point)
	, ui_(new Ui::EditFirePoint)
	, is_pos_changed_(false)
{
	ui_->setupUi(this);
	Bit_UnitSystem us = model_wrap_->get_structure()->get_cs().Get_UnitSystem();
	ui_->doubleSpinBox_X->setDecimals(model_wrap_->GetLengthPrecisionHint());
	ui_->doubleSpinBox_X->setSuffix(model_wrap_->GetLengthUnit());
	ui_->doubleSpinBox_X->setMinimum(0);
	ui_->doubleSpinBox_X->setMaximum(INT_MAX);
	ui_->doubleSpinBox_X->setSingleStep(1.0 / us.Get_LengthCoefficient());

	ui_->doubleSpinBox_Y->setDecimals(model_wrap_->GetLengthPrecisionHint());
	ui_->doubleSpinBox_Y->setSuffix(model_wrap_->GetLengthUnit());
	ui_->doubleSpinBox_Y->setMinimum(0);
	ui_->doubleSpinBox_Y->setMaximum(INT_MAX);
	ui_->doubleSpinBox_Y->setSingleStep(1.0 / us.Get_LengthCoefficient());
	ui_->doubleSpinBox_Y->setEnabled(false);

	Bit_Point2D pos = fire_point_->get_pos();
	double x = pos.Get_x();
	double y = pos.Get_y(); 
	ui_->doubleSpinBox_X->setValue(x);
	//Y坐标限制为0
	y = 0;
	ui_->doubleSpinBox_Y->setValue(y);

}
EditFirePointDialog::~EditFirePointDialog()
{
	delete ui_;
}
void EditFirePointDialog::accept()
{
	Bit_Point2D pos = fire_point_->get_pos();
	double x = pos.Get_x();
	double y = pos.Get_y();
	double new_x = ui_->doubleSpinBox_X->value();
	double new_y = ui_->doubleSpinBox_Y->value();
	if(x != new_x || y != new_y)
	{
		fire_point_->set_pos(Bit_Point2D(new_x, new_y));
		is_pos_changed_ = true;
	}
	QDialog::accept();
}

AddFirePointDialog::AddFirePointDialog(WarheadModelWrap* model_wrap, QWidget* parent)
	: model_(model_wrap->get_structure())
	, model_wrap_(model_wrap)
	, QDialog(parent)
	, ui_(new Ui::EditFirePoint)
	, fire_point_(0)
{
	Q_ASSERT_X(model_, "AddFirePointDialog::AddFirePointDialog", "model=NULL");
	ui_->setupUi(this);
	Bit_UnitSystem us = model_wrap_->get_structure()->get_cs().Get_UnitSystem();
	ui_->doubleSpinBox_X->setDecimals(model_wrap_->GetLengthPrecisionHint());
	ui_->doubleSpinBox_X->setSuffix(model_wrap_->GetLengthUnit());
	ui_->doubleSpinBox_X->setMinimum(0);
	model_->UpdateLength();
	double length = model_->get_character_data().length;
	ui_->doubleSpinBox_X->setMaximum(length);
	ui_->doubleSpinBox_X->setSingleStep(1.0 / us.Get_LengthCoefficient());

	ui_->doubleSpinBox_Y->setDecimals(model_wrap_->GetLengthPrecisionHint());
	ui_->doubleSpinBox_Y->setSuffix(model_wrap_->GetLengthUnit());
	ui_->doubleSpinBox_Y->setEnabled(false);
	//Y坐标限制为0
	ui_->doubleSpinBox_Y->setValue(0);
	ui_->doubleSpinBox_X->setValue(length/2);
}
AddFirePointDialog::~AddFirePointDialog()
{
	delete ui_;
}

void AddFirePointDialog::accept()
{
	double x = ui_->doubleSpinBox_X->value();
	double y = ui_->doubleSpinBox_Y->value();
	fire_point_ = model_->AddFirePoint(Bit_Point2D(x, y));
	QDialog::accept();
}