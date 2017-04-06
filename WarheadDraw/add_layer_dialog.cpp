#include "add_layer_dialog.h"
#include "ui_add_layer.h"
#include <WarheadModelData/WarheadModelWrap.h>
#include <WarheadModelData/warhead_section.h>
#include <WarheadModelData/warhead_fragment_layer.h>
#include <MaterialLib/materiallib.h>
#include <BasicTool/expandqtcore.h>

AddLayerDialog::AddLayerDialog(WarheadModelWrap* model_wrap, WarheadSection* section, WarheadLayer* layer, QWidget* parent)
	: QDialog(parent)
	, model_wrap_(model_wrap)
	, section_(section)
	, current_layer_(layer)
	, new_layer_(0)
	, ui_(new Ui::AddLayer)
{
	Q_ASSERT_X(section_ != 0, "AddLayerDialog::AddLayerDialog", "section == NULL");
	ui_->setupUi(this);
	QButtonGroup* btn_group = new QButtonGroup(this);
	btn_group->addButton(ui_->radioButton_inner);
	btn_group->addButton(ui_->radioButton_outer);
	if(!current_layer_)
		current_layer_ = section_->get_layers().first();
	if(current_layer_ == section_->get_layers().first())
	{
		ui_->radioButton_inner->hide();
		ui_->radioButton_outer->hide();
	}

	QStringList layer_types;
	int index = 0;
	layer_types.push_back(ExpandQtCore::fromGBK("壳体")); int_2_layer_type_.insert(index++, kShell);
	layer_types.push_back(ExpandQtCore::fromGBK("球形破片")); int_2_layer_type_.insert(index++, kSphereFragment);
	layer_types.push_back(ExpandQtCore::fromGBK("内衬")); int_2_layer_type_.insert(index++, kLining);

	ui_->comboBox_layer_type->addItems(layer_types);
	ui_->comboBox_layer_type->setCurrentIndex(0);

	QHBoxLayout* layout = new QHBoxLayout(ui_->widget_shape_param);
	layout->setContentsMargins(0, 10, 0, 0);
	layout->addWidget(CreateShapeParamWidget(int_2_layer_type_.value(0)));

	connect(ui_->comboBox_layer_type, SIGNAL(currentIndexChanged(int)), this, SLOT(on_layer_type_changed(int)));
	//设置材料库
	material_guid_2_name_ = model_wrap_->get_metal_lib()->GetAllGuidAndNames();
	ui_->comboBox_material->addItems(material_guid_2_name_.values());
}

AddLayerDialog::~AddLayerDialog()
{
	delete ui_;
}
void AddLayerDialog::accept()
{
	new_layer_ = GetLayer();
	bool outer_pos = ui_->radioButton_outer->isChecked();
	section_->AddLayer(new_layer_, current_layer_, outer_pos);
	return QDialog::accept();
}

WarheadLayer* AddLayerDialog::GetLayer()
{
	WarheadLayerType layer_type = int_2_layer_type_.value(ui_->comboBox_layer_type->currentIndex());
	QFormLayout* layout = dynamic_cast<QFormLayout*>(ui_->widget_shape_param->layout()->itemAt(0)->widget()->layout());
	Q_ASSERT(layout);
	ShapeThickness shape_thickness;
	WarheadLayer* layer = 0;
	switch(layer_type)
	{
	case kShell:
	case kLining:
		{
			shape_thickness.type = kUp;
			QRadioButton* equal_thickness_btn = dynamic_cast<QRadioButton*>(layout->itemAt(0, QFormLayout::LabelRole)->widget());
			Q_ASSERT(equal_thickness_btn);
			if(equal_thickness_btn->isChecked())
			{
				QDoubleSpinBox* box = dynamic_cast<QDoubleSpinBox*>(layout->itemAt(0, QFormLayout::FieldRole)->widget());
				Q_ASSERT(box);
				shape_thickness.left = box->value();
				shape_thickness.right = shape_thickness.left;
			}
			else
			{
				QDoubleSpinBox* box_1 = dynamic_cast<QDoubleSpinBox*>(layout->itemAt(2, QFormLayout::FieldRole)->widget()); Q_ASSERT(box_1);
				QDoubleSpinBox* box_2 = dynamic_cast<QDoubleSpinBox*>(layout->itemAt(3, QFormLayout::FieldRole)->widget()); Q_ASSERT(box_2);
				shape_thickness.left = box_1->value();
				shape_thickness.right = box_2->value();
			}
			layer = new WarheadLayer;
			layer->set_thickness(shape_thickness);
		}
		break;
	case kSphereFragment:
		//厚度 r * n * 2
		{
			QDoubleSpinBox* box_1 = dynamic_cast<QDoubleSpinBox*>(layout->itemAt(0, QFormLayout::FieldRole)->widget()); Q_ASSERT(box_1);
			QDoubleSpinBox* box_2 = dynamic_cast<QDoubleSpinBox*>(layout->itemAt(1, QFormLayout::FieldRole)->widget()); Q_ASSERT(box_2);
			//QDoubleSpinBox* box_3 = dynamic_cast<QDoubleSpinBox*>(layout->itemAt(2, QFormLayout::FieldRole)->widget()); Q_ASSERT(box_3);

			SphereFragmentLayer* sphere_layer = new SphereFragmentLayer(section_, box_1->value());
			sphere_layer->set_layer_num(box_2->value());
			//sphere_layer->set_circle_lay_space(box_3->value());
			layer = sphere_layer;
		}
		break;
	}
	layer->set_layer_type(layer_type);
	QString material_guid = material_guid_2_name_.key(ui_->comboBox_material->currentText());
	layer->set_material(model_wrap_->get_metal_lib()->GetMaterial(material_guid));
	return layer;
}

void AddLayerDialog::on_layer_type_changed(int index)
{
	QWidget* widget = CreateShapeParamWidget(int_2_layer_type_.value(index));
	if(widget)
	{
		QHBoxLayout* layout = dynamic_cast<QHBoxLayout*>(ui_->widget_shape_param->layout());
		Q_ASSERT(layout);
		QWidget* old_widget = layout->itemAt(0)->widget();
		layout->replaceWidget(old_widget, widget);
		delete old_widget;
	}
}

void AddLayerDialog::on_layer_pos_changed(bool checked)
{

}

QWidget* AddLayerDialog::CreateShapeParamWidget(WarheadLayerType layer_type)
{
	QWidget* widget = new QWidget;
	QFormLayout* layout = new QFormLayout(widget);
	layout->setContentsMargins(0, 0, 0, 0);
	switch(layer_type)
	{
	case kShell:
	case kLining:
		{
			QRadioButton* btn = new QRadioButton(ExpandQtCore::fromGBK("等厚度"), widget);
			btn->setChecked(true);
			layout->addRow(btn, CreateDoubleSpinBox(10, widget));
			layout->addRow(new QRadioButton(ExpandQtCore::fromGBK("非等厚度"), 0));
			layout->addRow(ExpandQtCore::fromGBK("左端厚"), CreateDoubleSpinBox(10, widget));
			layout->addRow(ExpandQtCore::fromGBK("右端厚"), CreateDoubleSpinBox(15, widget));
		}
		break;
	case kSphereFragment:
		{
			QDoubleSpinBox* r_box = CreateDoubleSpinBox(5, widget);
			r_box->setDecimals(r_box->decimals());
			layout->addRow(ExpandQtCore::fromGBK("半径"), r_box);

			QDoubleSpinBox* box = CreateDoubleSpinBox(3, widget);
			box->setSingleStep(1);
			box->setMinimum(1);
			box->setMaximum(100);
			box->setDecimals(0);
			box->setSuffix("");
			box->setValue(3);
			layout->addRow(ExpandQtCore::fromGBK("层数"), box);
		}
		break;
	}
	return widget;
}
QDoubleSpinBox* AddLayerDialog::CreateDoubleSpinBox(double mm_value, QWidget* parent)
{
	Bit_UnitSystem us = model_wrap_->get_structure()->get_cs().Get_UnitSystem();
	QDoubleSpinBox* box = new QDoubleSpinBox(parent);
	box->setDecimals(model_wrap_->GetLengthPrecisionHint());
	box->setSuffix(model_wrap_->GetLengthUnit());
	box->setMinimum(1.0 / us.Get_LengthCoefficient());
	box->setMaximum(INT_MAX);
	box->setSingleStep(1.0 / us.Get_LengthCoefficient());
	box->setValue(mm_value / us.Get_LengthCoefficient());
	return box;
}


EditLayerDialog::EditLayerDialog(WarheadModelWrap* model_wrap, WarheadSection* section, WarheadLayer* layer, QWidget* parent)
	: AddLayerDialog(model_wrap, section, layer, parent)
	, is_type_or_thickness_changed_(false)
	, is_type_changed_(false)
	, new_type_layer_(0)
{
	Q_ASSERT_X(layer != 0, "EditLayerDialog::EditLayerDialog", "layer == NULL");
	ui_->radioButton_inner->hide();
	ui_->radioButton_outer->hide();
	ui_->comboBox_layer_type->setCurrentIndex(int_2_layer_type_.key(current_layer_->get_layer_type()));
	const Material* mtl = current_layer_->get_material();
	if(mtl)
		ui_->comboBox_material->setCurrentIndex(ui_->comboBox_material->findText(mtl->get_name()));
	UpdateShapeParamWidget();
}
EditLayerDialog::~EditLayerDialog()
{

}
void EditLayerDialog::accept()
{
	WarheadLayerType layer_type = int_2_layer_type_.value(ui_->comboBox_layer_type->currentIndex());
	WarheadLayer* new_layer = GetLayer();
	if(current_layer_->get_layer_type() != layer_type)
	{
		//类型发生改变
		WarheadLayer* new_layer = GetLayer();
		//替换
		section_->ReplaceLayer(current_layer_, new_layer);
		is_type_or_thickness_changed_ = true;
		is_type_changed_ = true;
		new_type_layer_ = new_layer;
	}
	else
	{
		//材料
		current_layer_->set_material(new_layer->get_material());
		switch(layer_type)
		{
		case kShell:
		case kLining:
			{
				ShapeThickness current_thickess = current_layer_->get_thickness();
				ShapeThickness new_thickness = new_layer->get_thickness();
				if(current_thickess != new_thickness)
				{
					current_layer_->set_thickness(new_thickness);
					is_type_or_thickness_changed_ = true;
				}
			}
			break;
		case kSphereFragment:
			{
				SphereFragmentLayer* sphere_current_layer = dynamic_cast<SphereFragmentLayer*>(current_layer_);
				SphereFragmentLayer* sphere_new_layer = dynamic_cast<SphereFragmentLayer*>(new_layer);
				if(sphere_current_layer->get_r() != sphere_new_layer->get_r())
				{
					sphere_current_layer->set_r(sphere_new_layer->get_r());
					is_type_or_thickness_changed_ = true;
				}
				if(sphere_current_layer->get_layer_num() != sphere_new_layer->get_layer_num())
				{
					sphere_current_layer->set_layer_num(sphere_new_layer->get_layer_num());
					is_type_or_thickness_changed_ = true;
				}
			}
			break;
		}
		delete new_layer;
	}
	QDialog::accept();
	
}
void EditLayerDialog::UpdateShapeParamWidget()
{
	WarheadLayerType layer_type = int_2_layer_type_.value(ui_->comboBox_layer_type->currentIndex());
	QFormLayout* layout = dynamic_cast<QFormLayout*>(ui_->widget_shape_param->layout()->itemAt(0)->widget()->layout());
	Q_ASSERT(layout);
	switch(layer_type)
	{
	case kShell:
		{
			ShapeThickness shape_thickness = current_layer_->get_thickness();
			QRadioButton* equal_thickness_btn = dynamic_cast<QRadioButton*>(layout->itemAt(0, QFormLayout::LabelRole)->widget());
			Q_ASSERT(equal_thickness_btn);
			if(shape_thickness.left == shape_thickness.right)
			{
				equal_thickness_btn->setChecked(true);
				QDoubleSpinBox* box = dynamic_cast<QDoubleSpinBox*>(layout->itemAt(0, QFormLayout::FieldRole)->widget());
				Q_ASSERT(box);
				box->setValue(shape_thickness.left);
			}
			else
			{
				QRadioButton* non_equal_thickness_btn = dynamic_cast<QRadioButton*>(layout->itemAt(1, QFormLayout::SpanningRole)->widget());
				Q_ASSERT(non_equal_thickness_btn);
				non_equal_thickness_btn->setChecked(true);
				equal_thickness_btn->setChecked(false);
				QDoubleSpinBox* box_1 = dynamic_cast<QDoubleSpinBox*>(layout->itemAt(2, QFormLayout::FieldRole)->widget()); Q_ASSERT(box_1);
				QDoubleSpinBox* box_2 = dynamic_cast<QDoubleSpinBox*>(layout->itemAt(3, QFormLayout::FieldRole)->widget()); Q_ASSERT(box_2);
				box_1->setValue(shape_thickness.left);
				box_2->setValue(shape_thickness.right);
			}
		}
		break;
	case kSphereFragment:
		//厚度 r * n * 2
		{
			QDoubleSpinBox* box_1 = dynamic_cast<QDoubleSpinBox*>(layout->itemAt(0, QFormLayout::FieldRole)->widget()); Q_ASSERT(box_1);
			QDoubleSpinBox* box_2 = dynamic_cast<QDoubleSpinBox*>(layout->itemAt(1, QFormLayout::FieldRole)->widget()); Q_ASSERT(box_2);
			//QDoubleSpinBox* box_3 = dynamic_cast<QDoubleSpinBox*>(layout->itemAt(2, QFormLayout::FieldRole)->widget()); Q_ASSERT(box_3);

			SphereFragmentLayer* layer = dynamic_cast<SphereFragmentLayer*>(current_layer_);
			Q_ASSERT(layer);
			box_1->setValue(layer->get_r());
			box_2->setValue(layer->get_layer_num());
			//box_3->setValue(layer->get_circle_lay_space());
		}
		break;
	}
}
