#include "scene_2d.h"
#include "shape_item.h"
#include "coordinate_item.h"
#include "grid_item.h"
#include <WarheadModelData/WarheadModelWrap.h>
#include <WarheadModelData/warhead_layer.h>
#include <WarheadModelData/warhead_section.h>
#include <WarheadModelData/warhead_model.h>
#include <WarheadModelData/warhead_fragment_layer.h>
#include <iostream>
#include <QtSvg>

Scene2D::Scene2D(QObject* parent) 
	: QGraphicsScene(parent)
	, coord_item_(0)
	, label_item_(0)
	, ver_line_item_(new QGraphicsLineItem)
	, hor_line_item_(new QGraphicsLineItem)
	, pos_tip_item_(new QGraphicsTextItem)
	, grid_delta_(20)
	, ctrl_key_press_(false)

{
	QPen pen;
	pen.setColor(Qt::black);
	pen.setStyle(Qt::DashLine);
	pen.setWidthF(0.8);
	ver_line_item_->setPen(pen);
	hor_line_item_->setPen(pen);
	addItem(ver_line_item_);
	addItem(hor_line_item_);
	addItem(pos_tip_item_);
	ver_line_item_->hide();
	ver_line_item_->hide();
	pos_tip_item_->hide();
	pos_tip_item_->setZValue(1);

	//栅格
	GridItem* grid_item = new GridItem(sceneRect(), grid_delta_);
	addItem(grid_item);
	grid_item->setPos(0, 0);
	grid_item_ = grid_item;
	connect(this, SIGNAL(sceneRectChanged(const QRectF&)), grid_item, SLOT(on_scene_rect_changed(const QRectF&)));


}
void Scene2D::SaveStructure(const QString& name)
{
	QSvgGenerator generator;
	generator.setFileName(name);
	QPainter painter;
	//label_item_->hide();
	grid_item_->hide();
	QRect rect = sceneRect().toRect();
	QRectF rect_shape = coord_item_->childrenBoundingRect();
	generator.setViewBox(rect_shape);
	generator.setSize(rect_shape.size().toSize());
	painter.begin(&generator);
	render(&painter, rect_shape, rect_shape);
	painter.end();
	//label_item_->show();
	grid_item_->show();
}
// 写入文件
bool Scene2D::Write(const QString& file_name) 
{ 
	SaveStructure(file_name); 
	return true;
}

void Scene2D::set_model_wrap(WarheadModelWrap* model_wrap)
{
	model_wrap_ = model_wrap;
	set_model(model_wrap_->get_structure());
}

void Scene2D::Draw()
{
	removeItem(coord_item_);
	coord_item_ = 0;
	label_item_ = 0;
	item_2_layer_.clear();
	if(model_)
	{
		Bit_2DCSWithExpAndUS& cs_2d = model_->get_cs();
		Coordinate2D* coord_item = new Coordinate2D(cs_2d);
		coord_item_ = coord_item;
		shape_item_parent_ = new NullItem(coord_item_);
		SetCoordinateItem(coord_item);

		model_coord_item_ = new ModelCoordItem(model_wrap_, &cs_2d, coord_item_);

		if(WarheadEndCap* left_end_cap = model_->get_left_end_cap())
		{
			EndCapItem* item = new EndCapItem(model_wrap_, left_end_cap, shape_item_parent_);
			item_2_layer_.insert(item, left_end_cap);
		}
		if(WarheadEndCap* right_end_cap = model_->get_right_end_cap())
		{
			EndCapItem* item = new EndCapItem(model_wrap_, right_end_cap, shape_item_parent_);
			item_2_layer_.insert(item, right_end_cap);
		}
		foreach(WarheadSection* section, model_->get_sections())
		{
			foreach(WarheadLayer* layer, section->get_layers())
			{
				LayerItem* item = 0;
				if(SphereFragmentLayer* sphere_layer = dynamic_cast<SphereFragmentLayer*>(layer))
					item = new SphereFragmentLayerItem(model_wrap_, sphere_layer, section, shape_item_parent_);
				 else
					 item = new LayerItem(model_wrap_, layer, section, shape_item_parent_);
				item_2_layer_.insert(item, layer);
			}
		}
		foreach(WarheadFirePoint* fire_point, model_->get_fire_points())
		{
			FirePointItem* item = new FirePointItem(model_wrap_, fire_point, shape_item_parent_);
			item_2_layer_.insert(item, fire_point);
		}

		//标注
		label_item_ = new LabelItem(model_wrap_, shape_item_parent_, coord_item);
	}
}
void Scene2D::SetCoordinateItem(Coordinate2D* coord_item)
{
	coord_item_ = coord_item;
	addItem(coord_item_);
	coord_item_->setPos(0, 0);
}
void Scene2D::AddPartShapeItem(ShapeItem* shape_item)
{
	shape_item->setParentItem(shape_item_parent_);
	connect(shape_item, SIGNAL(sig_part_move(const QPointF&)), this, SLOT(on_part_move(const QPointF&)));
}
void Scene2D::on_part_move(const QPointF& pos)
{
	QRectF rect = sceneRect();
	if((int)(pos.x()) % grid_delta_ == 0)
	{
		hor_line_item_->setLine(pos.x(), rect.topLeft().y(), pos.x(), rect.bottomLeft().y());
		hor_line_item_->setVisible(true);
	}
	else
	{
		hor_line_item_->hide();
	}
	if((int)(pos.y()) % grid_delta_ == 0)
	{
		ver_line_item_->setLine(rect.topLeft().x(), pos.y(), rect.topRight().x(), pos.y());
		ver_line_item_->setVisible(true);
	}
	else
	{
		ver_line_item_->hide();
	}
	QString tip = QString("[%1,%2]").arg(pos.x()).arg(-pos.y());
	pos_tip_item_->setPlainText(tip);
	pos_tip_item_->setPos(pos);
	pos_tip_item_->setVisible(true);
}
void Scene2D::mousePressEvent(QGraphicsSceneMouseEvent * mouseEvent)
{
	QList<QGraphicsItem*> _items = items(mouseEvent->scenePos());
	ShapeItem* shape_item = 0;
	WarheadNode* node = 0;
	if(_items.size() > 0)
	{
		ShapeItem* shape_item = dynamic_cast<ShapeItem*>(_items.first());
		if(shape_item)
		{
			node = item_2_layer_.value(shape_item, 0);

		}
	}
	//显示节点信息
	if(label_item_)
		label_item_->ShowNodeInfo(node);
	emit sig_current_node_changed(node);
	QGraphicsScene::mousePressEvent(mouseEvent);
}
void Scene2D::mouseDoubleClickEvent(QGraphicsSceneMouseEvent * mouseEvent)
{
	QList<QGraphicsItem*> _items = items(mouseEvent->scenePos());
	ShapeItem* shape_item = 0;
	WarheadNode* node = 0;
	if(_items.size() > 0)
	{
		ShapeItem* shape_item = dynamic_cast<ShapeItem*>(_items.first());
		if(shape_item)
			node = item_2_layer_.value(shape_item, 0);
	}
	emit sig_view_property(node);
	QGraphicsScene::mouseDoubleClickEvent(mouseEvent);
}
void Scene2D::mouseMoveEvent(QGraphicsSceneMouseEvent * mouseEvent)
{
	QGraphicsScene::mouseMoveEvent(mouseEvent);
}

void Scene2D::mouseReleaseEvent(QGraphicsSceneMouseEvent * mouseEvent)
{
	hor_line_item_->hide();
	ver_line_item_->hide();
	pos_tip_item_->hide();
	QGraphicsScene::mouseReleaseEvent(mouseEvent);
}

void Scene2D::keyPressEvent(QKeyEvent * keyEvent)
{
	if(keyEvent->key() == Qt::Key_Control)
		ctrl_key_press_ = true;
}
void Scene2D::keyReleaseEvent(QKeyEvent * keyEvent)
{
	ctrl_key_press_ = false;
}

//下移一层
void Scene2D::LayerLower(QGraphicsItem* item)
{

}
//上移一层
void Scene2D::LayerUpper(QGraphicsItem* item)
{

}
//置于顶层
void Scene2D::LayerTop(QGraphicsItem* item)
{
	QList<QGraphicsItem*> collideitems = collidingItems(item);
	for(int i=collideitems.size()-1; i>=0; --i)
	{
		collideitems.at(i)->stackBefore(item);
	}
	update();
}
//置于底层
void Scene2D::LayerBottom(QGraphicsItem* item)
{

}
void Scene2D::Update()
{
	foreach(ShapeItem* shape_item, item_2_layer_.keys())
		shape_item->Update();
	label_item_->Update();
	//LayerTop(coord_item_);
}

void Scene2D::on_add_section(WarheadSection* section)
{
	Q_ASSERT(section);
	WarheadLayer* layer = section->get_layers().first();
	Q_ASSERT(layer);
	ShapeItem* shape_item = new LayerItem(model_wrap_, layer, section);
	AddPartShapeItem(shape_item);
	shape_item->setPos(0, 0);
	UpdateWhenAdd(shape_item);
	item_2_layer_.insert(shape_item, layer);
}
void Scene2D::on_delete_section(WarheadSection* section)
{
	foreach(WarheadLayer* layer, section->get_layers())
		RemoveNode(layer);
	Update();
}
void Scene2D::on_add_layer(WarheadSection* section, WarheadLayer* layer)
{
	Q_ASSERT(layer);
	ShapeItem* shape_item = 0;
	if(SphereFragmentLayer* sphere_layer = dynamic_cast<SphereFragmentLayer*>(layer))
		shape_item = new SphereFragmentLayerItem(model_wrap_, sphere_layer, 0);
	else
		shape_item = new LayerItem(model_wrap_, layer, section);
	AddPartShapeItem(shape_item);
	shape_item->setPos(0, 0);
	UpdateWhenAdd(shape_item);
	item_2_layer_.insert(shape_item, layer);
}
void Scene2D::on_delete_layer(WarheadSection* section, WarheadLayer* layer) 
{ 
	RemoveNode(layer);
	Update();
}
void Scene2D::on_add_end_cap(WarheadEndCap* end_cap)
{
	Q_ASSERT(end_cap);
	ShapeItem* shape_item = new EndCapItem(model_wrap_, end_cap);
	AddPartShapeItem(shape_item);
	shape_item->setPos(0, 0);
	UpdateWhenAdd(shape_item);
	item_2_layer_.insert(shape_item, end_cap);
}
void Scene2D::on_delete_end_cap(WarheadEndCap* end_cap) 
{ 
	RemoveNode(end_cap);
	Update();
}
void Scene2D::on_add_fire_point(WarheadFirePoint* fire_point)
{
	Q_ASSERT(fire_point);
	ShapeItem* shape_item = new FirePointItem(model_wrap_, fire_point);
	AddPartShapeItem(shape_item);
	shape_item->setPos(0, 0);
	item_2_layer_.insert(shape_item, fire_point);
	
}
void Scene2D::on_delete_fire_point(WarheadFirePoint* fire_point) 
{ 
	RemoveNode(fire_point);
	foreach(ShapeItem* shape_item, item_2_layer_.keys())
	{
		if(FirePointItem* fire_point_item = dynamic_cast<FirePointItem*>(shape_item))
			shape_item->Update();
	}
}

void Scene2D::UpdateWhenAdd(QGraphicsItem* new_item)
{
	foreach(ShapeItem* item, item_2_layer_.keys())
	{
		item->Update();
		if(FirePointItem* fire_point_item = dynamic_cast<FirePointItem*>(item))
			new_item->stackBefore(fire_point_item);
	}
	//new_item->stackBefore(model_coord_item_);
	//new_item->stackBefore(coord_item_);
	
	label_item_->Update();
}

void Scene2D::on_warhead_node_changed(WarheadNode* node)
{
	Q_ASSERT(node);
	if(WarheadFirePoint* fire_point = dynamic_cast<WarheadFirePoint*>(node))
	{
		item_2_layer_.key(fire_point)->Update();
		return ;
	}
	foreach(ShapeItem* item, item_2_layer_.keys())
	{
		item->Update();
	}
	label_item_->Update();
}

void Scene2D::on_layer_type_changed(WarheadSection* section, WarheadLayer* old_layer, WarheadLayer* new_layer)
{
	if(old_layer == label_item_->GetShowInfoNode())
	{
		label_item_->ShowNodeInfo(0);
	}
	ShapeItem* shape_item = item_2_layer_.key(old_layer, 0);
	if(shape_item)
	{
		shape_item->setParentItem(0);
		removeItem(shape_item);
		item_2_layer_.remove(shape_item);
		on_add_layer(section, new_layer);
	}
}


void Scene2D::on_cs_changed()
{
	model_coord_item_->Update();
}
void Scene2D::RemoveNode(WarheadNode* node)
{
	Q_ASSERT(node);
	ShapeItem* item = item_2_layer_.key(node, 0);
	Q_ASSERT(item);
	removeItem(item);
	item_2_layer_.remove(item);
	if(node == label_item_->GetShowInfoNode())
	{
		label_item_->ShowNodeInfo(0);
	}
}
