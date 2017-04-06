#include "segment_item.h"


Segment2D::Segment2D(const Bit_Segment2D& s2d, QGraphicsItem* parent)
	: s2d_(s2d)
	, QGraphicsItem(parent)
{

}

QRectF Segment2D::boundingRect() const
{
	Bit_Point2D p1 = s2d_.Get_FristPoint();
	Bit_Point2D p2 = s2d_.Get_SencodPoint();
	//判断是线段还是圆锥或圆台
	if(p1.Get_y() * p2.Get_y() < 0)
		return QRectF(QPointF(p1.Get_x(), p2.Get_y()), QPointF(p2.Get_x(), p2.Get_y()));
	else
	{
		//X轴方向的距离
		double dx = fabs(p2.Get_x() - p1.Get_x());
		double max_y = std::max(fabs(p1.Get_y()), fabs(p2.Get_y()));
		return QRectF(p1.Get_x(), p2.Get_y(), dx, 2*max_y);
	}
}

void Segment2D::paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget)
{
	QPen pen;
	pen.setWidth(3);
	painter->setPen(pen);
	Bit_Point2D p1 = s2d_.Get_FristPoint();
	Bit_Point2D p2 = s2d_.Get_SencodPoint();
	QPointF _p1(p1.Get_x(), p1.Get_y());
	QPointF _p2(p2.Get_x(), p2.Get_y());
	painter->drawLine(_p1, _p2);
	//判断是线段还是圆锥或圆台
//	if(p1.Get_y() * p2.Get_y() >= 0)
//	{
//		QPointF _p3 = _p1;
//		_p3.ry() = -_p3.y();
//		QPointF _p4 = _p2;
//		_p4.ry() = -_p4.y();
//		painter->drawLine(_p3, _p4);
//		painter->drawLine(_p1, _p3);
//		painter->drawLine(_p2, _p4);
//	}
}