#include "edit_cs_dialog.h"
#include "ui_edit_cs_dialog.h"
#include <WarheadModelData/WarheadModelWrap.h>
#include <BIT2DCSSupport/Bit_2DCSWithExpAndUS.h>
#include <BasicTool/expandqtcore.h>

EditCSDialog::EditCSDialog(WarheadModelWrap* model_wrap, QWidget* parent)
	: model_wrap_(model_wrap)
	, cs_(&model_wrap->get_structure()->get_cs())
	, QDialog(parent)
{
	ui_ = new Ui::EditCS;
	ui_->setupUi(this);
	Bit_2DCSWithExplain cs_explain = cs_->Get_2DCSWithExplain();
	Bit_2DCS cs_2d = cs_explain.Get_CS();
	Bit_Point2D origin = cs_2d.Get_OriginalPoint();
	Bit_Point2D x_v = cs_2d.Get_XAixVector();
	//Bit_Point2D y_v = cs_2d.Get_YAixVector();

	Bit_UnitSystem us = model_wrap_->get_structure()->get_cs().Get_UnitSystem();
	ui_->doubleSpinBox->setDecimals(model_wrap_->GetLengthPrecisionHint());
	ui_->doubleSpinBox->setSuffix(model_wrap_->GetLengthUnit());
	ui_->doubleSpinBox->setMinimum(0);

	ui_->doubleSpinBox->setValue(origin.Get_x());
	if(x_v.Get_x() == 1 && x_v.Get_y() == 0)
	{
		ui_->comboBox->setCurrentIndex(0);
	}
	else
	{
		ui_->comboBox->setCurrentIndex(1);
	}

	ui_->textEdit->setText(ExpandQtCore::fromGBK(cs_explain.Get_Explain().c_str()));

}
EditCSDialog::~EditCSDialog()
{
	delete ui_;
}

void EditCSDialog::accept()
{
	Bit_2DCSWithExplain cs_explain;
	Bit_Point2D x_v(1, 0);
	if(ui_->comboBox->currentIndex() == 1)
	{
		x_v.Set_x(-1);
	}
	Bit_2DCS cs(Bit_Point2D(ui_->doubleSpinBox->value(), 0), 1, x_v);
	cs_explain.Set_Initial(0, "CS", ui_->textEdit->toPlainText().toLocal8Bit().data(), cs);
	Bit_UnitSystem us = cs_->Get_UnitSystem();
	cs_->Set_Initial(cs_explain, us);
	QDialog::accept();
}