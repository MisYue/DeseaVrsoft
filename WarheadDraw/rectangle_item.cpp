#include "rectangle_item.h"

//绘制坐标系与矩形坐标系不同
Rectangle2D::Rectangle2D(const Bit_Rectangle2D& r2d, QGraphicsItem* parent)
	: r2d_(r2d)
	, ShapeItem(parent)
{

}

QRectF Rectangle2D::boundingRect() const
{
	Bit_Point2D top_left = r2d_.Get_TopLeftP();
	QRectF rect(top_left.Get_x(), -top_left.Get_y(), r2d_.Get_DX(), r2d_.Get_DY());
	return rect;
}

void Rectangle2D::paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget)
{
	QPen pen;
	pen.setWidth(3);
	painter->setPen(pen);
	painter->drawRect(boundingRect());
}