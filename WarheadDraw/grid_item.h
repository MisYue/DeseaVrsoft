#pragma once
#include <QtWidgets>

class GridItem : public QObject, public QGraphicsItem
{
	Q_OBJECT
public:
	GridItem(const QRectF& rect, int delta = 20);
	virtual QRectF boundingRect() const;
	virtual void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget = 0);
	double get_delta() const { return delta_; }
public slots:
	void on_scene_rect_changed(const QRectF& rect);
protected:
	QPainterPath path_;
	int delta_;
	void CreatePath(const QRectF& rect);
};