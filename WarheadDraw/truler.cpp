#include "truler.h"
#include <iostream>

//View缩放时，标尺刻度值如何改变

//初始时，1像素代表1mm

//放大1倍时，1像素代表0.5mm
static double old_ver = 0;


TRuler::TRuler(QWidget* parent, TDirection dire, int min_value)
	: QLabel(parent)
	, dire_(dire)
	, hor_offset_(0)
	, ver_offset_(0)
	, max_ver_offset_(0)
	, min_value_(min_value)
	, scale_(1)
	, radio_(1)
{
	setStyleSheet("font: 12px; font-family: \"Times\";");
}

TRuler::~TRuler()
{

}
void TRuler::set_direction(TDirection dire)
{
	dire_ = dire;
	update();
}

void TRuler::paintEvent(QPaintEvent* ev)
{
	QPainter painter(this);
	painter.save();
	double radio = 1;
	//QTransform transform;
	//transform.scale(radio, radio);
	//painter.setTransform(transform);

	if(dire_ == kHor)
	{
		int i = 0;
		double w = width();
		while(((int)(i + hor_offset_/radio))%10 != 0 && i<w)
			++i;
		for(; i<w; i+=10)
		{
			int v = i + hor_offset_/radio;
			if(v % 50 == 0)
			{
				painter.drawLine(QLineF(QPointF(i*radio, height() - 10), QPointF(i*radio, height())));
				painter.drawText(QPointF(i*radio, height()/2), QString::number((i+hor_offset_/radio)));
			}
			else if(v % 10 == 0)
			{
				painter.drawLine(QLineF(QPointF(i*radio, height() - 5), QPointF(i*radio, height())));
			}
		}

	}
	else
	{
		int x = width();
		for(int i=0; i<=height(); ++i)
		{
			if((i+ver_offset_) % 50 == 0)
			{
				painter.drawLine(QLineF(QPointF(x, i), QPointF(x-10, i)));
				painter.drawText(QPointF(x - 35, i), QString::number((-(i+ver_offset_))));
			}
			else if((i+ver_offset_) % 10 == 0)
			{
				painter.drawLine(QLineF(QPointF(x, i), QPointF(x-5, i)));
			}
		}
	}
	painter.restore();
	QLabel::paintEvent(ev);
}

void TRuler::slot_horValueChanged(int value)
{
	hor_offset_ = value;
	update();
}

void TRuler::slot_verValueChanged(int value)
{
	ver_offset_ = value;
	update();
}

void TRuler::slot_verRangeChanged(int min, int max)
{
	max_ver_offset_ = max;
	update();
}

void TRuler::slot_scale(double s)
{
	//scale_ = s;
	//radio_ /= scale_;

	//update();
}
