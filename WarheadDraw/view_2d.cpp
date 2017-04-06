#include "view_2d.h"
#include "ui_view_2d.h"
#include "coordinate_item.h"
#include "shape_item.h"
#include "scale_view_2d.h"
#include "scene_2d.h"
#include "add_section_dialog.h"
#include "add_layer_dialog.h"
#include "add_end_cap_dialog.h"
#include "edit_fire_point_dialog.h"
#include "model_property_dialog.h"
#include "edit_cs_dialog.h"
#include <WarheadModelData/WarheadModelWrap.h>
#include <BasicTool/expandqtcore.h>
#include <WarheadModelData/warhead_model.h>
#include <WarheadModelData/warhead_section.h>

View2D::View2D(QWidget* parent)
	: QMainWindow(parent)
	, ui_(new Ui::View2D)
	, model_wrap_(0)
	, model_(0)
	, only_view_(false)
{
	ui_->setupUi(this);
	//ui_->htruler->set_direction(kHor);
	//ui_->vtruler->set_direction(kVer);
	view_ = ui_->graphicsView;
	scene_ = view_->get_scene();
	connect(this, SIGNAL(sig_add_section(WarheadSection*)), scene_, SLOT(on_add_section(WarheadSection*)));
	connect(this, SIGNAL(sig_add_layer(WarheadSection*, WarheadLayer*)), scene_, SLOT(on_add_layer(WarheadSection*, WarheadLayer*)));
	connect(this, SIGNAL(sig_add_fire_point(WarheadFirePoint*)), scene_, SLOT(on_add_fire_point(WarheadFirePoint*)));
	connect(this, SIGNAL(sig_add_end_cap(WarheadEndCap*)), scene_, SLOT(on_add_end_cap(WarheadEndCap*)));
	connect(this, SIGNAL(sig_warhead_node_changed(WarheadNode*)), scene_, SLOT(on_warhead_node_changed(WarheadNode*)));
	connect(this, SIGNAL(sig_delete_section(WarheadSection*)), scene_, SLOT(on_delete_section(WarheadSection*)));
	connect(this, SIGNAL(sig_delete_layer(WarheadSection*, WarheadLayer*)), scene_, SLOT(on_delete_layer(WarheadSection*, WarheadLayer*)));
	connect(this, SIGNAL(sig_delete_fire_point(WarheadFirePoint*)), scene_, SLOT(on_delete_fire_point(WarheadFirePoint*)));
	connect(this, SIGNAL(sig_delete_end_cap(WarheadEndCap*)), scene_, SLOT(on_delete_end_cap(WarheadEndCap*)));
	connect(this, SIGNAL(sig_layer_type_changed(WarheadSection*, WarheadLayer*, WarheadLayer*)), scene_, SLOT(on_layer_type_changed(WarheadSection*, WarheadLayer*, WarheadLayer*)));

	connect(scene_, SIGNAL(sig_current_node_changed(WarheadNode*)), this, SLOT(on_current_node_changed(WarheadNode*)));
	connect(scene_, SIGNAL(sig_view_property(WarheadNode*)), this, SLOT(on_view_node_property(WarheadNode*)));

	//connect(view_->horizontalScrollBar(), SIGNAL(valueChanged(int)), ui_->htruler, SLOT(slot_horValueChanged(int)));
	//connect(view_->verticalScrollBar(), SIGNAL(valueChanged(int)), ui_->vtruler, SLOT(slot_verValueChanged(int)));
	//connect(view_->verticalScrollBar(), SIGNAL(rangeChanged(int, int)), ui_->vtruler, SLOT(slot_verRangeChanged(int, int)));

	QToolBar* tool_bar = new QToolBar(this);
	addToolBar(Qt::BottomToolBarArea, tool_bar);

	QWidget* widget = new QWidget(this);
	tool_bar->addWidget(widget);
	QHBoxLayout* h_layout = new QHBoxLayout(widget);
	h_layout->addWidget(new QLabel(ExpandQtCore::fromGBK("Ëõ·Å"), this));
	QComboBox* comboBox_radio = new QComboBox(this);
	h_layout->addWidget(comboBox_radio);
	comboBox_radio_ = comboBox_radio;
	h_layout->addWidget(new QLabel("%", this));
	connect(view_, SIGNAL(sig_scale(double)), this, SLOT(on_view_scal_changed(double)));
	
	QStringList radios;
	radios << "25" << "50" << "75" << "100" << "150" << "200";
	comboBox_radio->addItems(radios);
	connect(comboBox_radio, SIGNAL(currentTextChanged(const QString&)), this, SLOT(on_view_radio_changed(const QString&)));
	comboBox_radio->setCurrentText("100");

	add_section_action_ = CreateAction(ExpandQtCore::fromGBK("Ìí¼Ó¶Î"), "", SLOT(on_add_section()));
	view_->addAction(add_section_action_);
	tool_bar->addAction(add_section_action_);

	delete_section_action_ = CreateAction(ExpandQtCore::fromGBK("É¾³ý¶Î"), "", SLOT(on_delete_section()));
	view_->addAction(delete_section_action_);
	tool_bar->addAction(delete_section_action_);

	add_layer_action_ = CreateAction(ExpandQtCore::fromGBK("Ìí¼Ó²ã"), "", SLOT(on_add_layer()));
	view_->addAction(add_layer_action_);
	tool_bar->addAction(add_layer_action_);

	delete_layer_action_ = CreateAction(ExpandQtCore::fromGBK("É¾³ý²ã"), "", SLOT(on_delete_layer()));
	view_->addAction(delete_layer_action_);
	tool_bar->addAction(delete_layer_action_);

	add_end_cap_action_ = CreateAction(ExpandQtCore::fromGBK("Ìí¼Ó¶Ë¸Ç"), "", SLOT(on_add_end_cap()));
	view_->addAction(add_end_cap_action_);
	tool_bar->addAction(add_end_cap_action_);

	delete_end_cap_action_ = CreateAction(ExpandQtCore::fromGBK("É¾³ý¶Ë¸Ç"), "", SLOT(on_delete_end_cap()));
	view_->addAction(delete_end_cap_action_);
	tool_bar->addAction(delete_end_cap_action_);

	add_fire_point_action_ = CreateAction(ExpandQtCore::fromGBK("Ìí¼ÓÆð±¬µã"), "", SLOT(on_add_fire_point()));
	view_->addAction(add_fire_point_action_);
	tool_bar->addAction(add_fire_point_action_);

	delete_fire_point_action_ = CreateAction(ExpandQtCore::fromGBK("É¾³ýÆð±¬µã"), "", SLOT(on_delete_fire_point()));
	view_->addAction(delete_fire_point_action_);
	tool_bar->addAction(delete_fire_point_action_);

	view_property_action_ = CreateAction(ExpandQtCore::fromGBK("ÊôÐÔ"), "", SLOT(on_view_property()));
	view_->addAction(view_property_action_);
	tool_bar->addAction(view_property_action_);
	if(!only_view_)
	{
		tool_bar->hide();
	}
}

View2D::~View2D()
{
	delete ui_;
}
QList<QAction*>  View2D::get_actions() const
{
	return view_->actions();
}
WarheadDrawBase* View2D::GetPainter2D()
{
	return scene_;
}

void View2D::set_model_wrap(WarheadModelWrap* model_wrap)
{
	Reset();
	model_wrap_ = model_wrap;
	model_ = model_wrap_->get_structure();
	scene_->set_model_wrap(model_wrap_);
	view_->centerOn(0, 0);
}
void View2D::SaveStructure(const QString& name)
{
	scene_->SaveStructure(name);
}
void View2D::on_view_radio_changed(const QString& text)
{
	QString current_text = comboBox_radio_->currentText();
	double radio = current_text.toDouble()/100;
	QTransform transform;
	transform.scale(radio, radio);
	view_->setTransform(transform);
}
void View2D::on_view_scal_changed(double s)
{
	QString current_text = comboBox_radio_->currentText();
	double current_radio = current_text.toDouble();
	double last_radio = current_radio;
	current_radio *= s;
	if(current_radio < 10)
		current_radio = 10;
	if(current_radio > 500)
		current_radio = 500;
	comboBox_radio_->setCurrentText(QString::number(current_radio, 'f', 0));
}
void View2D::on_add_section()
{
	Q_ASSERT(model_);
	WarheadSection* current_section = 0;
	if(current_node_.type == kNTLayer)
	{
		WarheadLayer* current_layer = dynamic_cast<WarheadLayer*>(current_node_.node);
		if(current_layer)
		{
			current_section = model_->GetSection(current_layer);
		}
	}
	AddSectionDialog dialog(model_wrap_, current_section, this);
	if(QDialog::Accepted == dialog.exec())
	{
		WarheadSection* section = dialog.get_new_section();
		model_->UpdateEndCap();
		emit sig_add_section(section);
	}
}
void View2D::on_delete_section()
{
	Q_ASSERT(model_);
	WarheadLayer* layer = dynamic_cast<WarheadLayer*>(current_node_.node);
	Q_ASSERT(layer);
	WarheadSection* section = model_->GetSection(layer);
	Q_ASSERT(section);
	QList<WarheadLayer*> layers = section->get_layers();
	emit sig_delete_section(section);
	model_->DeleteSection(section);
	scene_->Update();
}
void View2D::on_add_layer()
{
	Q_ASSERT(model_);
	WarheadSection* current_section = 0;
	WarheadLayer* current_layer = 0;
	if(current_node_.type == kNTLayer)
	{
		current_layer = dynamic_cast<WarheadLayer*>(current_node_.node);
		if(current_layer)
		{
			current_section = model_->GetSection(current_layer);
			AddLayerDialog dialog(model_wrap_, current_section, current_layer, this);
			if(QDialog::Accepted == dialog.exec())
			{
				WarheadLayer* layer = dialog.get_new_layer();
				model_->UpdateEndCap();
				emit sig_add_layer(current_section, layer);
			}
		}
	}
}
void View2D::on_delete_layer()
{
	Q_ASSERT(model_);
	WarheadLayer* layer = dynamic_cast<WarheadLayer*>(current_node_.node);
	Q_ASSERT(layer);
	WarheadSection* section = model_->GetSection(layer);
	Q_ASSERT(section);
	section->DeleteLayer(layer);
	model_->UpdateEndCap();
	emit sig_delete_layer(section, layer);
}
void View2D::on_add_end_cap()
{
	Q_ASSERT(model_);
	if(model_->GetNumSection() > 0 && (model_->get_left_end_cap() == 0 || model_->get_right_end_cap() == 0))
	{
		AddEndCapDialog dialog(model_wrap_, this);
		if(QDialog::Accepted == dialog.exec())
		{
			WarheadEndCap* end_cap = dialog.get_new_end_cap();
			emit sig_add_end_cap(end_cap);
		}
	}
}
void View2D::on_delete_end_cap()
{
	Q_ASSERT(model_);
	WarheadEndCap* end_cap = dynamic_cast<WarheadEndCap*>(current_node_.node);
	Q_ASSERT(end_cap);
	if(end_cap == model_->get_left_end_cap())
		model_->DeleteLeftEndCap();
	else
		model_->DeleteRightEndCap();
	emit sig_delete_end_cap(end_cap);
}
void View2D::on_add_fire_point()
{
	Q_ASSERT(model_);
	AddFirePointDialog dialog(model_wrap_, this);
	if(QDialog::Accepted == dialog.exec())
	{
		WarheadFirePoint* fire_point = dialog.get_new_fire_point();
		emit sig_add_fire_point(fire_point);
	}
}
void View2D::on_delete_fire_point()
{
	Q_ASSERT(model_);
	WarheadFirePoint* fire_point = dynamic_cast<WarheadFirePoint*>(current_node_.node);
	Q_ASSERT(fire_point);
	model_->DeleteFirePoint(fire_point->get_id());
	emit sig_delete_fire_point(fire_point);
}
void View2D::on_view_property()
{
	if(current_node_.type == kNTCS)
	{
		on_cs_edited();
	}
	else
	{
		on_view_node_property(current_node_.node);
	}
}
void View2D::on_current_node_changed(WarheadNode* node)
{
	if(model_ == 0)
		return ;
	QList<QAction*> actions = view_->actions();
	foreach(QAction* action, actions)
		action->setEnabled(false);
	view_property_action_->setEnabled(true);
	if(model_->GetNumSection() > 0 && (model_->get_left_end_cap() == 0 || model_->get_right_end_cap() == 0))
		add_end_cap_action_->setEnabled(true);

	current_node_.node = node;
	if(0 == node)
	{
		current_node_.type = kNTModel;
		if(model_->get_sections().size() == 0)
			add_section_action_->setEnabled(true);
	}
	else if(WarheadLayer* layer = dynamic_cast<WarheadLayer*>(node))
	{
		current_node_.type = kNTLayer;
		add_section_action_->setEnabled(true);
		add_layer_action_->setEnabled(true);
		add_fire_point_action_->setEnabled(true);
		if(layer->get_layer_type() == kCharge)
			delete_section_action_->setEnabled(true);
		else
			delete_layer_action_->setEnabled(true);
	}
	else if(WarheadEndCap* end_cap = dynamic_cast<WarheadEndCap*>(node))
	{
		current_node_.type = kNTEndCap;
		delete_end_cap_action_->setEnabled(true);
	}
	else if(WarheadFirePoint* fire_point = dynamic_cast<WarheadFirePoint*>(node))
	{
		current_node_.type = kNTFirePoint;
		delete_fire_point_action_->setEnabled(true);
	}
}
void View2D::on_current_node_changed(const Node& node)
{
	if(node.type == kNTCS)
	{
		current_node_.type = node.type;
		current_node_.node = node.node;
		QList<QAction*> actions = view_->actions();
		foreach(QAction* action, actions)
			action->setEnabled(false);
		view_property_action_->setEnabled(true); 
	}
	else
	{
		on_current_node_changed(node.node);
	}
}

void View2D::on_cs_changed()
{
	scene_->on_cs_changed();
}
void View2D::on_cs_edited()
{
	EditCSDialog dialog(model_wrap_, this);
	if(dialog.exec() == QDialog::Accepted)
	{
		scene_->on_cs_changed();
	}
}
void View2D::on_view_node_property(WarheadNode* node)
{
	Q_ASSERT(model_);
	bool is_changed= false;
	if(0 == node)
	{
		ModelPropertyDialog dialog(model_wrap_, this);
		if(QDialog::Accepted == dialog.exec())
		{
			if(dialog.IsNameChanged())
				emit sig_model_name_changed();
		}
	}
	else if(WarheadLayer* layer = dynamic_cast<WarheadLayer*>(node))
	{
		WarheadSection* section = model_->GetSection(layer);
		if(layer == section->get_layers().first())
		{
			EditSectionDialog dialog(model_wrap_, section, this);
			if(QDialog::Accepted == dialog.exec())
				is_changed = dialog.IsShapeChanged();
		}
		else
		{
			EditLayerDialog dialog(model_wrap_, section, layer, this);
			if(QDialog::Accepted == dialog.exec())
				if(dialog.IsTypeOrThicknessChanged())
				{
					model_->UpdateEndCap();
					if(dialog.IsTypeChanged())
						emit sig_layer_type_changed(section, layer, dialog.get_new_type_layer());
					else
						is_changed = true;
				}
		}
	}
	else if(WarheadEndCap* end_cap = dynamic_cast<WarheadEndCap*>(node))
	{		
		EditEndCapDialog dialog(model_wrap_, end_cap, this);
		if(QDialog::Accepted == dialog.exec())
			is_changed = dialog.IsLengthChanged();
	}
	else if(WarheadFirePoint* fire_point = dynamic_cast<WarheadFirePoint*>(node))
	{		
		EditFirePointDialog dialog(model_wrap_, fire_point, this);
		if(QDialog::Accepted == dialog.exec())
			is_changed = dialog.IsPosChanged();
	}

	if(is_changed)
		emit sig_warhead_node_changed(node);
}
void View2D::Reset()
{

}

QAction* View2D::CreateAction(const QString& text, const QString& icon, const char* slot)
{
	QAction* action = new QAction(QIcon(icon), text, this);
	action->setEnabled(false);
	bool result = connect(action, SIGNAL(triggered()), this, slot);
	return action;
}


