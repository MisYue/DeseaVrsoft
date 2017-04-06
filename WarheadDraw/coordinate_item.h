#pragma once
#include <BIT2DCSSupport/Bit_2DCSWithExpAndUS.h>
#ifdef pi
#undef pi
#endif
#include <QtWidgets>


class Coordinate2D : public QGraphicsItem
{
public:
	Coordinate2D(const Bit_2DCSWithExpAndUS& cs, QGraphicsItem* parent = 0);
	virtual QRectF boundingRect() const;
	virtual void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget = 0);
protected:
	const Bit_2DCSWithExpAndUS& cs_;
	QPainterPath path_;
};