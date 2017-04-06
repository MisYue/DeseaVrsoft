#include "view_structure.h"
#include "view_2d.h"
#include <WarheadModelData/warhead_model.h>
#include <WarheadModelData/warhead_layer.h>
#include <WarheadModelData/warhead_section.h>
#include <WarheadModelData/warhead_model.h>
#include <WarheadModelData/warhead_fragment_layer.h>
#include <BasicTool/expandqtcore.h>

ViewStructure::ViewStructure(QWidget* parent)
	: struture_tree_(new QTreeWidget(this))
	, view_2d_(0)
{
	setCentralWidget(struture_tree_);
	struture_tree_->setHeaderHidden(true);
	//connect(struture_tree_, SIGNAL(itemClicked(QTreeWidgetItem*, int)), this, SLOT(on_item_clicked(QTreeWidgetItem*, int)));
	connect(struture_tree_, SIGNAL(itemPressed(QTreeWidgetItem*, int)), this, SLOT(on_item_clicked(QTreeWidgetItem*, int)));
	//connect(struture_tree_, SIGNAL(itemSelectionChanged()), this, SLOT(on_item_changed()));

	struture_tree_->setContextMenuPolicy(Qt::ActionsContextMenu);
}
ViewStructure::~ViewStructure()
{

}
void ViewStructure::on_item_clicked(QTreeWidgetItem* item, int column)
{
	//WarheadNode* node = item_2_layer_.value(item, 0);
	//if(node)
	//{
	//	Node current_node;
	//	if(WarheadModel* model = dynamic_cast<WarheadModel*>(node))
	//		current_node.type = kNTModel;
	//	else if(WarheadLayer* layer = dynamic_cast<WarheadLayer*>(node))
	//		current_node.type = kNTLayer;
	//	else if(WarheadEndCap* end_cap = dynamic_cast<WarheadEndCap*>(node))
	//		current_node.type = kNTEndCap;
	//	else if(WarheadFirePoint* fire_point = dynamic_cast<WarheadFirePoint*>(node))
	//		current_node.type = kNTFirePoint;
	//	current_node.node = node;
	//	view_2d_->on_current_node_changed(current_node.node);
	//}
	//QTreeWidgetItem* item = 0;
	//QList<QTreeWidgetItem*> items = struture_tree_->selectedItems();
	//if(items.size() > 0)
	//	item = items.first();
	Node current_node;
	if(coord_item_ == item)
	{
		current_node.type = kNTCS;
	}
	else
	{
		WarheadNode* node = item_2_layer_.value(item, 0);
		if(node)
		{
			current_node.node = node;
			if(WarheadModel* model = dynamic_cast<WarheadModel*>(node))
			{
				current_node.type = kNTModel;
				current_node.node = 0;
			}
			else if(WarheadLayer* layer = dynamic_cast<WarheadLayer*>(node))
				current_node.type = kNTLayer;
			else if(WarheadEndCap* end_cap = dynamic_cast<WarheadEndCap*>(node))
				current_node.type = kNTEndCap;
			else if(WarheadFirePoint* fire_point = dynamic_cast<WarheadFirePoint*>(node))
				current_node.type = kNTFirePoint;
		}
	}
	view_2d_->on_current_node_changed(current_node);
}

void ViewStructure::on_item_changed()
{
	QTreeWidgetItem* item = 0;
	QList<QTreeWidgetItem*> items = struture_tree_->selectedItems();
	if(items.size() > 0)
		item = items.first();
	Node current_node;
	if(coord_item_ == item)
	{
		current_node.type = kNTCS;
	}
	else
	{
		WarheadNode* node = item_2_layer_.value(item, 0);
		if(node)
		{
			current_node.node = node;
			if(WarheadModel* model = dynamic_cast<WarheadModel*>(node))
			{
				current_node.type = kNTModel;
				current_node.node = 0;
			}
			else if(WarheadLayer* layer = dynamic_cast<WarheadLayer*>(node))
				current_node.type = kNTLayer;
			else if(WarheadEndCap* end_cap = dynamic_cast<WarheadEndCap*>(node))
				current_node.type = kNTEndCap;
			else if(WarheadFirePoint* fire_point = dynamic_cast<WarheadFirePoint*>(node))
				current_node.type = kNTFirePoint;
		}
	}
	view_2d_->on_current_node_changed(current_node);
}

void ViewStructure::set_view_2d(View2D* view_2d)
{
	view_2d_ = view_2d;
	Q_ASSERT(view_2d_);
	struture_tree_->addActions(view_2d_->get_actions());
	//连接与View2D之间的信号和槽
	connect(view_2d_, SIGNAL(sig_add_section(WarheadSection*)), this, SLOT(on_add_section(WarheadSection*)));
	connect(view_2d_, SIGNAL(sig_add_layer(WarheadSection*, WarheadLayer*)), this, SLOT(on_add_layer(WarheadSection*, WarheadLayer*)));
	connect(view_2d_, SIGNAL(sig_add_fire_point(WarheadFirePoint*)), this, SLOT(on_add_fire_point(WarheadFirePoint*)));
	connect(view_2d_, SIGNAL(sig_add_end_cap(WarheadEndCap*)), this, SLOT(on_add_end_cap(WarheadEndCap*)));
	connect(view_2d_, SIGNAL(sig_warhead_node_changed(WarheadNode*)), this, SLOT(on_warhead_node_changed(WarheadNode*)));

	connect(view_2d_, SIGNAL(sig_delete_section(WarheadSection*)), this, SLOT(on_delete_section(WarheadSection*)));
	connect(view_2d_, SIGNAL(sig_delete_layer(WarheadSection*, WarheadLayer*)), this, SLOT(on_delete_layer(WarheadSection*, WarheadLayer*)));
	connect(view_2d_, SIGNAL(sig_delete_fire_point(WarheadFirePoint*)), this, SLOT(on_delete_fire_point(WarheadFirePoint*)));
	connect(view_2d_, SIGNAL(sig_delete_end_cap(WarheadEndCap*)), this, SLOT(on_delete_end_cap(WarheadEndCap*)));
	connect(view_2d_, SIGNAL(sig_model_name_changed()), this, SLOT(on_model_name_changed()));
}

QTreeWidgetItem* ViewStructure::AddItem(const QString& text, QTreeWidgetItem* parent)
{
	QTreeWidgetItem* item = new QTreeWidgetItem;
	item->setText(0, text);
	if(parent)
		parent->addChild(item);
	return item;
}
void ViewStructure::Reset()
{
	WarheadModel* model = view_2d_->get_model();
	struture_tree_->clear();
	item_2_layer_.clear();
	if(model)
	{
		QTreeWidgetItem* model_item = AddItem(model->get_name());
		item_2_layer_.insert(model_item, model);

		struture_tree_->addTopLevelItem(model_item);


		coord_item_ = AddItem(ExpandQtCore::fromGBK("坐标系"));
		model_item->addChild(coord_item_);
		if(WarheadEndCap* left_end_cap = model->get_left_end_cap())
			item_2_layer_.insert(AddItem(ExpandQtCore::fromGBK("左端盖"), coord_item_), left_end_cap);
		if(WarheadEndCap* right_end_cap = model->get_right_end_cap())
			item_2_layer_.insert(AddItem(ExpandQtCore::fromGBK("右端盖"), coord_item_), right_end_cap);

		int section_id = 0;
		foreach(WarheadSection* section, model->get_sections())
		{
			QTreeWidgetItem* section_item = AddItem(ExpandQtCore::fromGBK("段")+ QString::number(++section_id), coord_item_);
			QList<WarheadLayer*> layers = section->get_layers();
			QList<WarheadLayer*>::iterator iter = layers.begin();
			item_2_layer_.insert(section_item, *iter);
			int layer_id = 0;
			while(++iter != layers.end())
			{
				item_2_layer_.insert(AddItem(ExpandQtCore::fromGBK("层")+QString::number(++layer_id), section_item), *iter);
			}
		}
		foreach(WarheadFirePoint* fire_point, model->get_fire_points())
			item_2_layer_.insert(AddItem(ExpandQtCore::fromGBK("起爆点") + QString::number(fire_point->get_id()+1), coord_item_), fire_point);

		struture_tree_->expandAll();
		struture_tree_->setCurrentItem(model_item);
		on_item_clicked(model_item, 0);
	}
}


void ViewStructure::on_add_section(WarheadSection* section)
{
	Reset();
}
void ViewStructure::on_delete_section(WarheadSection* section)
{
	Reset();

}
void ViewStructure::on_add_layer(WarheadSection* section, WarheadLayer* layer)
{
	Reset();

}
void ViewStructure::on_delete_layer(WarheadSection* section, WarheadLayer* layer)
{
	Reset();

}
void ViewStructure::on_add_end_cap(WarheadEndCap* end_cap)
{
	Reset();

}
void ViewStructure::on_delete_end_cap(WarheadEndCap* end_cap)
{
	Reset();

}
void ViewStructure::on_add_fire_point(WarheadFirePoint* fire_point)
{
	Reset();

}
void ViewStructure::on_delete_fire_point(WarheadFirePoint* fire_point)
{
	Reset();

}
void ViewStructure::on_warhead_node_changed(WarheadNode* node)
{
	Reset();

}
void ViewStructure::on_model_name_changed()
{
	Reset();
}

