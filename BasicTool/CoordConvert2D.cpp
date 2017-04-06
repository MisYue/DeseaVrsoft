#include "CoordConvert2D.h"
#include <cmath>

CoordConvert2D::CoordConvert2D(double rad, double translate_x, double translate_y)
	: rad_(rad)
	, translate_x_(translate_x)
	, translate_y_(translate_y)
{
}


CoordConvert2D::~CoordConvert2D(void)
{
}


// 正转
void CoordConvert2D::Convert(double& x, double& y)
{
	x -= translate_x_;
	y -= translate_y_;
	double cos_rad = cos(rad_);
	double sin_rad = sin(rad_);
	x = cos_rad*x + sin_rad*y;
	y = -sin_rad*x + cos_rad*y;
}


// 反转
void CoordConvert2D::Reverse(double& x, double& y)
{
	double cos_rad = cos(rad_);
	double sin_rad = sin(rad_);
	x = cos_rad*x - sin_rad*y;
	y = sin_rad*x + cos_rad*y;

	x += translate_x_;
	y += translate_y_;
}
