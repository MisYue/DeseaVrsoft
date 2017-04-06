#pragma once
#include "warhead_draw_global.h"
#include <QtWidgets>

class Scene2D;
class WARHEADDRAW_EXPORT ScaleView2D: public QGraphicsView
{
	Q_OBJECT
public:
	ScaleView2D(QWidget* parent = 0);
	Scene2D* get_scene() { return scene_; }
signals:
	void sig_scale(double s);
protected:
	virtual void wheelEvent(QWheelEvent * event);
	virtual void keyPressEvent(QKeyEvent * keyEvent);
	virtual void keyReleaseEvent(QKeyEvent * keyEvent);
	bool ctrl_key_press_;
	Scene2D* scene_;
};