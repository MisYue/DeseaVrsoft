#include "grid_item.h"

GridItem::GridItem(const QRectF& rect, int delta) : delta_(delta), QGraphicsItem(0)
{
	CreatePath(rect);
}

QRectF GridItem::boundingRect() const
{
	return path_.boundingRect();
}
void GridItem::paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget)
{
	QPen pen;
	pen.setStyle(Qt::DotLine);
	pen.setWidthF(0.4);
	pen.setColor(Qt::black);
	painter->setPen(pen);
	painter->drawPath(path_);
}
void GridItem::on_scene_rect_changed(const QRectF& rect)
{
	CreatePath(rect);
	prepareGeometryChange();
	update();
}

void GridItem::CreatePath(const QRectF& rect)
{
	QPointF top_left = rect.topLeft();
	QPointF bottom_left = rect.bottomLeft();

	double x_min = top_left.x();
	double x_max = rect.topRight().x();
	double y_min = top_left.y();
	double y_max = bottom_left.y();

	QPainterPath path;
	for(int i = ((int)(y_min) / 10) * 10; i<y_max; i+=delta_)
	{
		path.moveTo(x_min, i);
		path.lineTo(x_max, i);
	}

	for(int i = ((int)(x_min) / 10) * 10; i<x_max; i+=delta_)
	{
		path.moveTo(i, y_min);
		path.lineTo(i, y_max);
	}
	path_ = path;
}


