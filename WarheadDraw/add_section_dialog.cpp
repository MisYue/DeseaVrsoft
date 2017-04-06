#include "add_section_dialog.h"
#include "ui_add_section.h"
#include <WarheadModelData/WarheadModelWrap.h>
#include <WarheadModelData/warhead_section.h>
#include <WarheadModelData/warhead_model.h>
#include <MaterialLib/materiallib.h>
#include <BasicTool/expandqtcore.h>

//border-image: url(:/images/cone);
AddSectionDialog::AddSectionDialog(WarheadModelWrap* model_wrap, WarheadSection* section, QWidget* parent)
	: ui_(new Ui::AddSection)
	, current_section_(section)
	, new_section_(0)
	, model_wrap_(model_wrap)
	, model_(model_wrap->get_structure())

{
	Q_ASSERT_X(model_, "AddSectionDialog::AddSectionDialog", "model == NULL");
	ui_->setupUi(this);
	if(current_section_)
	{
		QString current_section_name = current_section_->get_name();
		//setWindowTitle(windowTitle() + ExpandQtCore::fromGBK("  当前段-") + current_section_name);
		ui_->checkBox_auto_align->setChecked(true);
		ui_->radioButto_right->setChecked(true);
		connect(ui_->checkBox_auto_align, SIGNAL(toggled(bool)), this, SLOT(on_auto_align_changed(bool)));
		connect(ui_->radioButto_left, SIGNAL(toggled(bool)), this, SLOT(on_add_pos_changed(bool)));
		connect(ui_->radioButto_right, SIGNAL(toggled(bool)), this, SLOT(on_add_pos_changed(bool)));
	}
	else
	{
		ui_->checkBox_auto_align->hide();
		ui_->radioButto_left->hide();
		ui_->radioButto_right->hide();
	}
	QStringList layer_types;
	int index = 0;
	layer_shape_types_.push_back(ExpandQtCore::fromGBK("圆台")); int_2_layer_shape_type_.insert(index++, kCone);
	layer_shape_types_.push_back(ExpandQtCore::fromGBK("卵形")); int_2_layer_shape_type_.insert(index++, kOval);
	layer_shape_types_.push_back(ExpandQtCore::fromGBK("圆柱")); int_2_layer_shape_type_.insert(index++, kCylinder);

	ui_->comboBox__shape_types->addItems(layer_shape_types_);
	ui_->comboBox__shape_types->setCurrentIndex(0);
	QHBoxLayout* layout = new QHBoxLayout(ui_->widget_shape_param);
	layout->setContentsMargins(0, 10, 0, 0);
	layout->addWidget(CreateShapeParamWidget(int_2_layer_shape_type_.value(0)));
	if(current_section_)
		on_auto_align_changed(ui_->checkBox_auto_align->isChecked());
	connect(ui_->comboBox__shape_types, SIGNAL(currentIndexChanged(int)), this, SLOT(on_shape_type_changed(int)));

	//设置材料库
	material_guid_2_name_ = model_wrap_->get_charge_lib()->GetAllGuidAndNames();
	ui_->comboBox__material->addItems(material_guid_2_name_.values());
	
}
AddSectionDialog::~AddSectionDialog()
{
	delete ui_;
}
void AddSectionDialog::on_shape_type_changed(int index)
{
	QWidget* widget = CreateShapeParamWidget(int_2_layer_shape_type_.value(index));
	if(widget)
	{
		QHBoxLayout* layout = dynamic_cast<QHBoxLayout*>(ui_->widget_shape_param->layout());
		Q_ASSERT(layout);
		QWidget* old_widget = layout->itemAt(0)->widget();
		layout->replaceWidget(old_widget, widget);
		delete old_widget;
		if(current_section_)
			on_auto_align_changed(ui_->checkBox_auto_align->isChecked());


	}
}
void AddSectionDialog::accept()
{
	if(ShapeDescribe* shape_describe = GetShape())
	{
		QString material_guid = material_guid_2_name_.key(ui_->comboBox__material->currentText());
		new_section_ = new WarheadSection(shape_describe, model_wrap_->get_charge_lib()->GetMaterial(material_guid));
		model_->AddSection(new_section_, current_section_, ui_->radioButto_left->isChecked());
	}
	QDialog::accept();
}
QWidget* AddSectionDialog::CreateShapeParamWidget(ShapeType shape_type)
{
	QWidget* widget = new QWidget;
	QFormLayout* layout = new QFormLayout(widget);
	layout->setContentsMargins(0, 0, 0, 0);
	switch(shape_type)
	{
	case kCone:
		layout->addRow(ExpandQtCore::fromGBK("R1"), CreateDoubleSpinBox(60, widget, 0));
		layout->addRow(ExpandQtCore::fromGBK("R2"), CreateDoubleSpinBox(90, widget));
		layout->addRow(ExpandQtCore::fromGBK("L"), CreateDoubleSpinBox(250, widget));
		ui_->widget_shape_pic->setStyleSheet("border-image: url(:/images/cone)");

		break;
	case kCylinder:
		layout->addRow(ExpandQtCore::fromGBK("R"), CreateDoubleSpinBox(60, widget));
		layout->addRow(ExpandQtCore::fromGBK("L"), CreateDoubleSpinBox(350, widget));
		ui_->widget_shape_pic->setStyleSheet("border-image: url(:/images/cylinder)");

		break;
	case kOval:
		layout->addRow(ExpandQtCore::fromGBK("H1"), CreateDoubleSpinBox(20, widget, 0));
		layout->addRow(ExpandQtCore::fromGBK("H2"), CreateDoubleSpinBox(60, widget));
		layout->addRow(ExpandQtCore::fromGBK("L"), CreateDoubleSpinBox(150, widget));
		layout->addRow(ExpandQtCore::fromGBK("R"), CreateDoubleSpinBox(550, widget));
		ui_->widget_shape_pic->setStyleSheet("border-image: url(:/images/oval)");

	}
	return widget;
}
QDoubleSpinBox* AddSectionDialog::CreateDoubleSpinBox(double mm_value, QWidget* parent, double mm_min)
{
	Bit_UnitSystem us = model_wrap_->get_structure()->get_cs().Get_UnitSystem();
	QDoubleSpinBox* box = new QDoubleSpinBox(parent);
	box->setDecimals(model_wrap_->GetLengthPrecisionHint());
	box->setSuffix(model_wrap_->GetLengthUnit());
	box->setMinimum(mm_min / us.Get_LengthCoefficient());
	box->setMaximum(INT_MAX);
	box->setSingleStep(1.0 / us.Get_LengthCoefficient());
	box->setValue(mm_value / us.Get_LengthCoefficient());
	return box;
}
void AddSectionDialog::on_auto_align_changed(bool checked)
{
	Q_ASSERT(current_section_ != 0);
	ShapeType shape_type = int_2_layer_shape_type_.value(ui_->comboBox__shape_types->currentIndex());
	int left_box_index = 0;
	int right_box_index = 1;
	switch(shape_type)
	{
	case kCone:
		break;
	case kOval:
		break;
	case kCylinder:
		right_box_index = 0;
		break;
	}
	QDoubleSpinBox* box = 0;
	QFormLayout* layout = dynamic_cast<QFormLayout*>(ui_->widget_shape_param->layout()->itemAt(0)->widget()->layout());
	Q_ASSERT(layout);
	if(ui_->radioButto_right->isChecked())
	{
		box = dynamic_cast<QDoubleSpinBox*>(layout->itemAt(left_box_index, QFormLayout::FieldRole)->widget());
		Q_ASSERT(box);
		if(checked)
		{
			double right_half_height = current_section_->get_inner_right_half_height();
			box->setValue(right_half_height);
		}
	}
	else
	{
		box = dynamic_cast<QDoubleSpinBox*>(layout->itemAt(right_box_index, QFormLayout::FieldRole)->widget());
		Q_ASSERT(box);
		if(checked)
		{
			double left_half_height = current_section_->get_inner_left_half_height();
			box->setValue(left_half_height);
		}
	}
	box->setEnabled(!checked);
}
void AddSectionDialog::on_add_pos_changed(bool checked)
{
	if(!ui_->checkBox_auto_align->isChecked())
		return ;
	Q_ASSERT(current_section_ != 0);
	ShapeType shape_type = int_2_layer_shape_type_.value(ui_->comboBox__shape_types->currentIndex());
	ShapeDescribe* shape_describe = 0;
	QFormLayout* layout = dynamic_cast<QFormLayout*>(ui_->widget_shape_param->layout()->itemAt(0)->widget()->layout());
	Q_ASSERT(layout);
	switch(shape_type)
	{
	case kCone:
		for(int i=0; i<3; ++i)
		{
			QDoubleSpinBox* box = dynamic_cast<QDoubleSpinBox*>(layout->itemAt(i, QFormLayout::FieldRole)->widget());
			Q_ASSERT(box);
			box->setEnabled(true);
		}
		if(ui_->radioButto_left->isChecked())
		{
			double left_half_height = current_section_->get_inner_left_half_height();
			QDoubleSpinBox* box = dynamic_cast<QDoubleSpinBox*>(layout->itemAt(1, QFormLayout::FieldRole)->widget());
			box->setEnabled(false);
			box->setValue(left_half_height);
		}
		else
		{
			double right_half_height = current_section_->get_inner_right_half_height();
			QDoubleSpinBox* box = dynamic_cast<QDoubleSpinBox*>(layout->itemAt(0, QFormLayout::FieldRole)->widget());
			box->setEnabled(false);
			box->setValue(right_half_height);
		}
		break;
	case kOval:
		for(int i=0; i<2; ++i)
		{
			QDoubleSpinBox* box = dynamic_cast<QDoubleSpinBox*>(layout->itemAt(i, QFormLayout::FieldRole)->widget());
			Q_ASSERT(box);
			box->setEnabled(true);
		}
		if(ui_->radioButto_left->isChecked())
		{
			double left_half_height = current_section_->get_inner_left_half_height();
			QDoubleSpinBox* box = dynamic_cast<QDoubleSpinBox*>(layout->itemAt(1, QFormLayout::FieldRole)->widget());
			box->setEnabled(false);
			box->setValue(left_half_height);
		}
		else
		{
			double right_half_height = current_section_->get_inner_right_half_height();
			QDoubleSpinBox* box = dynamic_cast<QDoubleSpinBox*>(layout->itemAt(0, QFormLayout::FieldRole)->widget());
			box->setEnabled(false);
			box->setValue(right_half_height);
		}
		break;
	case kCylinder:
		{
			for(int i=0; i<2; ++i)
			{
				QDoubleSpinBox* box = dynamic_cast<QDoubleSpinBox*>(layout->itemAt(i, QFormLayout::FieldRole)->widget());
				Q_ASSERT(box);
				box->setEnabled(true);
			}
			double r = 0;
			if(ui_->radioButto_left->isChecked())
				r = current_section_->get_inner_left_half_height();
			else
				r = current_section_->get_inner_right_half_height();
			QDoubleSpinBox* box = dynamic_cast<QDoubleSpinBox*>(layout->itemAt(0, QFormLayout::FieldRole)->widget());
			box->setEnabled(false);
			box->setValue(r);
		}
		break;
	}
}
ShapeDescribe* AddSectionDialog::GetShape()
{
	Bit_UnitSystem us = model_->get_cs().Get_UnitSystem();
	ShapeType shape_type = int_2_layer_shape_type_.value(ui_->comboBox__shape_types->currentIndex());
	ShapeDescribe* shape_describe = 0;
	QFormLayout* layout = dynamic_cast<QFormLayout*>(ui_->widget_shape_param->layout()->itemAt(0)->widget()->layout());
	Q_ASSERT(layout);
	switch(shape_type)
	{
	case kCone:
		{
			double d[3];
			for(int i=0; i<3; ++i)
			{
				QDoubleSpinBox* box = dynamic_cast<QDoubleSpinBox*>(layout->itemAt(i, QFormLayout::FieldRole)->widget());
				Q_ASSERT(box);
				d[i] = box->value();
			}
			shape_describe = new ConeDescribe(us, d[0], d[1], d[2]);
		}
		break;
	case kOval:
		{
			double d[4];
			for(int i=0; i<4; ++i)
			{
				QDoubleSpinBox* box = dynamic_cast<QDoubleSpinBox*>(layout->itemAt(i, QFormLayout::FieldRole)->widget());
				Q_ASSERT(box);
				d[i] = box->value();
			}
			shape_describe = new OvalDescribe(us, d[0], d[1], d[2], d[3]);
		}
		break;
	case kCylinder:
		{
			double d[2];
			for(int i=0; i<2; ++i)
			{
				QDoubleSpinBox* box = dynamic_cast<QDoubleSpinBox*>(layout->itemAt(i, QFormLayout::FieldRole)->widget());
				Q_ASSERT(box);
				d[i] = box->value();
			}
			shape_describe = new CylinderDescribe(us, d[0], d[1]);
		}
		break;
	}
	return shape_describe;
}

EditSectionDialog::EditSectionDialog(WarheadModelWrap* model_wrap, WarheadSection* section, QWidget* parent)
	: AddSectionDialog(model_wrap, section, parent)
	, is_shape_changed_(false)
	, next_section_(0)
	, previous_section_(0)
	, align_next_btn_(0)
	, align_previous_btn_(0)
{
	Q_ASSERT_X(section, "EditSectionDialog::EditSectionDialog", "section == NULL");
	ui_->radioButto_left->hide();
	ui_->radioButto_right->hide();
	ui_->checkBox_auto_align->hide();
	ui_->comboBox__shape_types->setCurrentIndex(int_2_layer_shape_type_.key(section->get_shape_describe()->get_shape_type()));
	const Material* mtl = section->GetFirstLayer()->get_material();
	if(mtl)
		ui_->comboBox__material->setCurrentIndex(ui_->comboBox__material->findText(mtl->get_name()));
	connect(ui_->comboBox__shape_types, SIGNAL(currentIndexChanged(int)), this, SLOT(on_shape_type_changed(int)));
	UpdateShapeParamWidget(section->get_shape_describe());

	next_section_ = model_->GetNextSection(current_section_);
	previous_section_ = model_->GetPreviousSection(current_section_);
	QVBoxLayout* layout = dynamic_cast<QVBoxLayout*>(this->layout());
	Q_ASSERT(layout);
	if(next_section_)
	{
		align_next_btn_ = new QCheckBox(ExpandQtCore::fromGBK("自动对齐下一段"), this);
		layout->insertWidget(2, align_next_btn_);
		align_next_btn_->setChecked(false);
		connect(align_next_btn_, SIGNAL(toggled(bool)), this, SLOT(on_auto_align_section_changed(bool)));
	}
	if(previous_section_)
	{
		align_previous_btn_ = new QCheckBox(ExpandQtCore::fromGBK("自动对齐前一段"), this);
		layout->insertWidget(2, align_previous_btn_);
		align_previous_btn_->setChecked(false);
		connect(align_previous_btn_, SIGNAL(toggled(bool)), this, SLOT(on_auto_align_section_changed(bool)));
	}
}
EditSectionDialog::~EditSectionDialog()
{

}

void EditSectionDialog::accept()
{
	if(ShapeDescribe* shape_describe = GetShape())
	{
		osg::ref_ptr<ShapeDescribe> current_shape = current_section_->get_shape_describe();
		if(!shape_describe->IsEqual(current_shape))
		{
			//基准点
			shape_describe->set_datum_point(current_shape->get_datum_point());
			double current_length = current_shape->get_shape_length();
			current_section_->set_shape_describe(shape_describe);
			is_shape_changed_ = true;
			//调整各段长度
			double dx = shape_describe->get_shape_length() - current_shape->get_shape_length();
			model_->AdjustAfterSectionPosX(current_section_, dx);
			//调整端盖
			model_->UpdateEndCap();
		}
	}
	WarheadLayer* charge_layer = current_section_->get_layers().first();
	QString material_guid = material_guid_2_name_.key(ui_->comboBox__material->currentText());
	charge_layer->set_material(model_wrap_->get_charge_lib()->GetMaterial(material_guid));
	QDialog::accept();
}

void EditSectionDialog::UpdateShapeParamWidget(const ShapeDescribe* shape)
{
	ShapeType shape_type = int_2_layer_shape_type_.value(ui_->comboBox__shape_types->currentIndex());
	QFormLayout* layout = dynamic_cast<QFormLayout*>(ui_->widget_shape_param->layout()->itemAt(0)->widget()->layout());
	Q_ASSERT(layout);
	QVector<double> values;
	switch(shape_type)
	{
	case kCone:
		{
			values.reserve(3);
			const ConeDescribe* cone = dynamic_cast<const ConeDescribe*>(shape);
			values.push_back(cone->get_left_r());
			values.push_back(cone->get_right_r());
			values.push_back(cone->get_length());
		}
		break;
	case kOval:
		{
			values.reserve(4);
			const OvalDescribe* oval = dynamic_cast<const OvalDescribe*>(shape);
			values.push_back(oval->get_left_half_height());
			values.push_back(oval->get_right_half_height());
			values.push_back(oval->get_length());
			values.push_back(oval->get_r());
		}
		break;
	case kCylinder:
		{
			values.reserve(2);
			const CylinderDescribe* cylinder = dynamic_cast<const CylinderDescribe*>(shape);
			values.push_back(cylinder->get_r());
			values.push_back(cylinder->get_length());
		}
		break;
	}
	for(int i=0, n=values.size(); i<n; ++i)
	{
		QDoubleSpinBox* box = dynamic_cast<QDoubleSpinBox*>(layout->itemAt(i, QFormLayout::FieldRole)->widget());
		Q_ASSERT(box);
		box->setValue(values[i]);
		box->setEnabled(true);
	}
}

void EditSectionDialog::on_auto_align_section_changed(bool checked)
{
	ShapeType shape_type = int_2_layer_shape_type_.value(ui_->comboBox__shape_types->currentIndex());
	int left_box_index = 0;
	int right_box_index = 1;
	switch(shape_type)
	{
	case kCone:
		break;
	case kOval:
		break;
	case kCylinder:
		right_box_index = 0;
		break;
	}
	QDoubleSpinBox* box = 0;
	QFormLayout* layout = dynamic_cast<QFormLayout*>(ui_->widget_shape_param->layout()->itemAt(0)->widget()->layout());
	Q_ASSERT(layout);
	if(sender() == align_next_btn_)
	{
		box = dynamic_cast<QDoubleSpinBox*>(layout->itemAt(right_box_index, QFormLayout::FieldRole)->widget());
		Q_ASSERT(box);
		if(checked)
		{
			double left_half_height = next_section_->get_inner_left_half_height();
			box->setValue(left_half_height);
		}
	}
	else if(sender() == align_previous_btn_)
	{
		box = dynamic_cast<QDoubleSpinBox*>(layout->itemAt(left_box_index, QFormLayout::FieldRole)->widget());
		Q_ASSERT(box);
		if(checked)
		{
			double right_half_height = previous_section_->get_inner_right_half_height();
			box->setValue(right_half_height);
		}
	}
	box->setEnabled(!checked);
}