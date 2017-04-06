#pragma once
#include "warhead_draw_global.h"
#include "WarheadDrawBase.h"
#include <QtWidgets>

class ShapeItem;
class Coordinate2D;
class View2D;
class WarheadSection;
class WarheadLayer;
class WarheadFirePoint;
class WarheadNode;
class WarheadEndCap;
class WarheadModel;
class NullItem;
class LabelItem;
class GridItem;
class WarheadModelWrap;
class WARHEADDRAW_EXPORT Scene2D : public QGraphicsScene, public WarheadDrawBase
{
	Q_OBJECT
public:
	Scene2D(QObject* parent=0);
	QGraphicsItem* CreateNewItem();
	//下移一层
	void LayerLower(QGraphicsItem* item);
	//上移一层
	void LayerUpper(QGraphicsItem* item);
	//置于顶层
	void LayerTop(QGraphicsItem* item);
	//置于底层
	void LayerBottom(QGraphicsItem* item);
	void Update();
	virtual void Draw();
	void SaveStructure(const QString& name);
	// 写入文件
	virtual bool Write(const QString& file_name);

	void set_model_wrap(WarheadModelWrap* model_wrap);
public slots:
	void on_part_move(const QPointF& pos);
	void on_add_section(WarheadSection* section);
	void on_delete_section(WarheadSection* section);
	void on_add_layer(WarheadSection* section, WarheadLayer* layer);
	void on_delete_layer(WarheadSection* section, WarheadLayer* layer);
	void on_add_end_cap(WarheadEndCap* end_cap);
	void on_delete_end_cap(WarheadEndCap* end_cap);
	void on_add_fire_point(WarheadFirePoint* fire_point);
	void on_delete_fire_point(WarheadFirePoint* fire_point);
	void on_warhead_node_changed(WarheadNode* node);
	void on_layer_type_changed(WarheadSection* section, WarheadLayer* old_layer, WarheadLayer* new_layer);
	void on_cs_changed();
signals:
	void sig_mouse_press(const QPointF& pos);
	void sig_current_node_changed(WarheadNode* node);
	void sig_view_property(WarheadNode* node);
protected:
	virtual void mousePressEvent(QGraphicsSceneMouseEvent * mouseEvent);
	virtual void mouseMoveEvent(QGraphicsSceneMouseEvent * mouseEvent);
	virtual void mouseReleaseEvent(QGraphicsSceneMouseEvent * mouseEvent);
	virtual void keyPressEvent(QKeyEvent * keyEvent);
	virtual void keyReleaseEvent(QKeyEvent * keyEvent);
	virtual void mouseDoubleClickEvent(QGraphicsSceneMouseEvent * mouseEvent);
	Coordinate2D* coord_item_;	//模型的坐标系
	//QGraphicsItem* coord_item_;	//模型的坐标系
	NullItem* shape_item_parent_;
	int grid_delta_;
	bool ctrl_key_press_;
	WarheadModelWrap* model_wrap_;
	//当部件的基准点被移动到栅格上时，高亮栅格线，提示用户
	QGraphicsLineItem* ver_line_item_;
	QGraphicsLineItem* hor_line_item_;
	QGraphicsTextItem* pos_tip_item_;
	LabelItem* label_item_;
	GridItem* grid_item_;
	QMap<ShapeItem*, WarheadNode*> item_2_layer_;
	ShapeItem* model_coord_item_;
	void UpdateWhenAdd(QGraphicsItem* new_item);
	void RemoveNode(WarheadNode* node);
	void SetCoordinateItem(Coordinate2D* coord_item);
	void AddPartShapeItem(ShapeItem* shape_item);
};