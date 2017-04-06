#include "coordinate_item.h"

QFont s_font_("Times", 9, QFont::Normal);

Coordinate2D::Coordinate2D(const Bit_2DCSWithExpAndUS& cs, QGraphicsItem* parent)
	: cs_(cs)
	, QGraphicsItem(parent)
{
	setFlag(ItemIsSelectable, true);
	setAcceptDrops(true);
	setAcceptHoverEvents(true);
	setAcceptedMouseButtons(Qt::LeftButton);

	QRectF bounding_rect = boundingRect();
	float x_axis_l = 50;
	float y_axis_l = 50;
	QFont font;
	font.setPointSizeF(15);
	QPointF origin(bounding_rect.center());
	QLineF x_axis(origin/* - QPointF(x_axis_l, 0)*/, origin + QPointF(x_axis_l, 0));
	QLineF y_axis(origin - QPointF(0, y_axis_l), origin/* + QPointF(0, y_axis_l)*/);
	path_.moveTo(x_axis.p1());
	path_.lineTo(x_axis.p2());
	path_.moveTo(y_axis.p1());
	path_.lineTo(y_axis.p2());
	//XÖá¼ýÍ·
	QPointF x_end = x_axis.p2();
	path_.moveTo(x_end);
	path_.lineTo(x_end - QPointF(10, 5));
	path_.moveTo(x_end);
	path_.lineTo(x_end - QPointF(10, -5));
	path_.addText(x_end + QPointF(10, 5), s_font_, "X");
	//YÖá¼ýÍ·
	QPointF y_end = y_axis.p1();
	path_.moveTo(y_end);
	path_.lineTo(y_end + QPointF(5, 10));
	path_.moveTo(y_end);
	path_.lineTo(y_end + QPointF(-5, 10));
	path_.addText(y_end + QPointF(-5, -10), s_font_, "Y");

}

QRectF Coordinate2D::boundingRect() const
{
	return path_.boundingRect();
}

void Coordinate2D::paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget)
{
	//QPen pen;
	//pen.setStyle(Qt::SolidLine);
	//pen.setWidthF(1);
	//pen.setColor(Qt::red);
	//painter->setPen(pen);
	//painter->drawPath(path_);

}