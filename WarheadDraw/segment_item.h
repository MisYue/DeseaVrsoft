#pragma once
#include <BIT2DModelSupport/Bit_Segment2D.h>
#ifdef pi
#undef pi
#endif
#include <QtWidgets>


class Segment2D : public QGraphicsItem
{
public:
	Segment2D(const Bit_Segment2D& s2d, QGraphicsItem* parent = 0);
	virtual QRectF boundingRect() const;
	virtual void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget = 0);
protected:
	const Bit_Segment2D& s2d_;
};