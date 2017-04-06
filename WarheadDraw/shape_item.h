#pragma once
#include <QtWidgets>

class WarheadModelWrap;
class WarheadNode;
class WarheadModel;
class WarheadLayer;
class WarheadSection;
class WarheadEndCap;
class WarheadFirePoint;
class SphereFragmentLayer;
class Bit_2DCSWithExpAndUS;

class NullItem : public QGraphicsItem
{
public:
	NullItem(QGraphicsItem* parent = 0) : QGraphicsItem(parent) {}
	virtual QRectF boundingRect() const { return QRectF(); }
	virtual void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget = 0){}
};
class ShapeItem : public QObject, public QGraphicsItem
{
	Q_OBJECT
public:
	ShapeItem(WarheadModelWrap* model_wrap, QGraphicsItem* parent = 0);
	virtual ~ShapeItem();
	virtual void Update(){ update(); }



protected:
	virtual bool Contains(const QPointF& pos) const { return false; }
	virtual void mousePressEvent(QGraphicsSceneMouseEvent * event);
	virtual void mouseMoveEvent(QGraphicsSceneMouseEvent * event);
	virtual void hoverMoveEvent(QGraphicsSceneHoverEvent * event);
	virtual void mouseReleaseEvent(QGraphicsSceneMouseEvent * event);
	static QFont s_font_;
	WarheadModelWrap* model_wrap_;

};

class LayerItem : public ShapeItem
{
public:
	LayerItem(WarheadModelWrap* model_wrap, WarheadLayer* layer, WarheadSection* section = 0, QGraphicsItem* parent = 0);
	virtual QRectF boundingRect() const;
	virtual void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget = 0);
	virtual QPainterPath shape() const;
	virtual void Update();
protected:
	WarheadLayer* layer_;
	QPainterPath path_;
	WarheadSection* section_;
	QPolygonF points_top_;
	QPolygonF points_bottom_;
	void UpdateInnerMostLayer();
	void UpdateOuterLayer();
	void UpdateBrush();
	QBrush brush_;
};

class EndCapItem : public ShapeItem
{
public:
	EndCapItem(WarheadModelWrap* model_wrap, WarheadEndCap* end_cap, QGraphicsItem* parent = 0);
	virtual QRectF boundingRect() const;
	virtual void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget = 0);
	virtual void Update();
protected:
	WarheadEndCap* end_cap_;
	QRectF rect_;
};

class FirePointItem : public ShapeItem
{
public:
	FirePointItem(WarheadModelWrap* model_wrap, WarheadFirePoint* fire_point, QGraphicsItem* parent = 0);
	virtual QRectF boundingRect() const;
	virtual void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget = 0);
	virtual QPainterPath shape() const;
	virtual void Update();

protected:
	WarheadFirePoint* fire_point_;
	double d_;
	QPainterPath path_;
};

class ModelCoordItem : public ShapeItem
{
public:
	ModelCoordItem(WarheadModelWrap* model_wrap, Bit_2DCSWithExpAndUS* cs, QGraphicsItem* parent = 0);
	virtual QRectF boundingRect() const;
	virtual void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget = 0);
	virtual QPainterPath shape() const;
	virtual void Update();

protected:
	QPainterPath path_;
	Bit_2DCSWithExpAndUS* cs_;
};

class SphereFragmentLayerItem : public LayerItem
{
public:
	SphereFragmentLayerItem(WarheadModelWrap* model_wrap, SphereFragmentLayer* layer, WarheadSection* section = 0, QGraphicsItem* parent = 0);
	//virtual QRectF boundingRect() const;
	virtual void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget = 0);
	virtual QPainterPath shape() const;
	virtual void Update();
protected:
	SphereFragmentLayer* frag_layer_;
};

class LabelItem : public ShapeItem
{
public:
	LabelItem(WarheadModelWrap* model_wrap, NullItem* shape_item_parent, QGraphicsItem* parent=0);
	virtual void Update();
	virtual QRectF boundingRect() const;
	virtual void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget = 0);
	virtual QPainterPath shape() const { return path_; }
	void ShowNodeInfo(WarheadNode* node);
	WarheadNode* GetShowInfoNode() { return info_node_; }
protected:
	int a_x_;
	int a_y_;
	QPainterPath path_;
	QPainterPath node_info_path_;
	NullItem* shape_item_parent_;
	WarheadModel* model_;
	WarheadNode* info_node_;
	QStringList CreateSectionLabel(WarheadSection* section);
	QStringList CreateNodeLabel(WarheadNode* node);
	void UpdateNodeInfo();

	void AddHorizontalLabel(QPainterPath& path, const QPointF& p1, const QPointF& p2, const QString& label, double h);
	void AddVerticalLabel(QPainterPath& path, const QPointF& p, const QString& label, double h, bool is_left);
	void AddVerticalLabel2(QPainterPath& path, const QPointF& p, double h, const QStringList& label);
	void AddVerticalLabel3(QPainterPath& path, const QPointF& p, const QString& label, double h, bool is_left);
	void AddVerticalLabel4(QPainterPath& path, const QPointF& p, const QStringList& label);

};