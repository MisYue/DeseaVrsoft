#pragma once
#include "basictool_global.h"

class BASICTOOL_EXPORT CoordConvert2D
{
public:
	CoordConvert2D(double rad, double translate_x, double translate_y);
	~CoordConvert2D(void);
	void set_rad(double rad) { rad_ = rad; }
	double get_rad() const { return rad_; }
	void set_translate_x(double x) { translate_x_ = x; }
	double get_translate_x() const { return translate_x_; }
	void set_translate_y(double y) { translate_y_ = y; }
	double get_translate_y() const { return translate_y_; }

	// 正转
	void Convert(double& x, double& y);
	// 反转
	void Reverse(double& x, double& y);
private:
	// 逆时针旋转弧度
	double rad_;
	// 往X轴正向平移距离
	double translate_x_;
	// 往Y轴正向平移距离
	double translate_y_;
};

