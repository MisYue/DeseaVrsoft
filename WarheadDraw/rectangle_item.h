#pragma once
#include "shape_item.h"
#include <BIT2DModelSupport/Bit_Rectangle2D.h>
#ifdef pi
#undef pi
#endif
#include <QtWidgets>


class Rectangle2D : public ShapeItem
{
public:
	Rectangle2D(const Bit_Rectangle2D& r2d, QGraphicsItem* parent = 0);
	virtual QRectF boundingRect() const;
	virtual void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget = 0);
protected:
	const Bit_Rectangle2D& r2d_;
};