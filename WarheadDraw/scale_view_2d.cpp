#include "scale_view_2d.h"
#include "scene_2d.h"
#include <iostream>

ScaleView2D::ScaleView2D(QWidget* parent) 
	: QGraphicsView(parent)
	, scene_(new Scene2D(this))
	, ctrl_key_press_(false)
{
	scene_->setItemIndexMethod(QGraphicsScene::NoIndex);
	setScene(scene_);
	setCacheMode(QGraphicsView::CacheBackground);
	setViewportUpdateMode(QGraphicsView::BoundingRectViewportUpdate);
	setRenderHint(QPainter::Antialiasing);
	setTransformationAnchor(QGraphicsView::AnchorUnderMouse);
	setDragMode(QGraphicsView::RubberBandDrag);
	setContextMenuPolicy(Qt::ActionsContextMenu);

	//屏幕的尺寸
	int width = QApplication::desktop()->width();
	int height = QApplication::desktop()->height();
	//场景矩形
	scene_->setSceneRect(-200, -800, 3000, 1600/*-width/5, -height/2, width, height*/);
}

void ScaleView2D::wheelEvent(QWheelEvent * event)
{
	if(ctrl_key_press_)
	{
		double s = 1;
		if(event->delta() > 0)
			s = 2;
		else
			s = 0.5 ;
		emit sig_scale(s);
	}
}

void ScaleView2D::keyPressEvent(QKeyEvent * keyEvent)
{
	if(keyEvent->key() == Qt::Key_Control)
		ctrl_key_press_ = true;
}
void ScaleView2D::keyReleaseEvent(QKeyEvent * keyEvent)
{
	ctrl_key_press_ = false;
}