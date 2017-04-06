#include "shape_describe.h"
#include <cmath>
#include <iostream>

Bit_Point2D operator * (const Bit_Point2D& p2d, double d)
{
	double x = p2d.Get_x();
	double y = p2d.Get_y();
	x *= d;
	y *= d;
	return Bit_Point2D(x, y);
}
//向量归一
void ShapeDescribe::VNormalize(Bit_Point2D& v)
{
	double x = v.Get_x();
	double y = v.Get_y();
	double l2 = sqrt(pow(x, 2) + pow(y, 2));
	x /= l2;
	y /= l2;
	v.Set_x(x);
	v.Set_y(y);
}

Bit_Point2D ShapeDescribe::RotateV(const Bit_Point2D& v, double degrees)
{
	double rad = degrees / (180/M_PI);
	double v_x = v.Get_x();
	double v_y = v.Get_y();
	double cos_rad = cos(rad);
	double sin_rad = sin(rad);
	return Bit_Point2D(v_x * cos_rad - v_y * sin_rad, v_x * sin_rad + v_y * cos_rad);
}

double ShapeDescribe::Length(const Bit_Point2D& p1, const Bit_Point2D& p2)
{
	double x1 = p1.Get_x();
	double x2 = p2.Get_x();
	double y1 = p1.Get_y();
	double y2 = p2.Get_y();
	return sqrt(pow(x1-x2, 2) + pow(y1-y2, 2));
}

bool ShapeDescribe::IsEqual(const ShapeDescribe* shape) const
{
	if(!shape)
		return false;
	if(this == shape)
		return true;
	if(shape->shape_type_ != shape_type_)
		return false;
	switch(shape_type_)
	{
	case kCone:
	case kCylinder:
		return (*this) == (*shape);
	case kOval:
		{
			const OvalDescribe* oval_1 = dynamic_cast<const OvalDescribe*>(this);
			const OvalDescribe* oval_2 = dynamic_cast<const OvalDescribe*>(shape);
			return (*oval_1) == (*oval_2);
		}
	}
	return false;
}

ShapeDescribe* ShapeDescribe::CreateShape(ShapeType type, const QString& describe)
{
	ShapeDescribe* shape = 0;
	QStringList strs = describe.split(",");
	switch(type)
	{
	case kCone:
		{
			Q_ASSERT(strs.size() == 5);
			shape = new ConeDescribe(strs[2].toDouble(), strs[3].toDouble(), strs[4].toDouble());
		}
		break;
	case kCylinder:
		{
			Q_ASSERT(strs.size() == 4);
			shape = new CylinderDescribe(strs[2].toDouble(), strs[3].toDouble());
		}
		break;
	case kOval:
		{
			Q_ASSERT(strs.size() == 6);
			shape = new OvalDescribe(strs[2].toDouble(), strs[3].toDouble(), strs[5].toDouble(), strs[4].toDouble());
		}
		break;
	}
	if(shape)
		shape->set_datum_point(Bit_Point2D(strs[0].toDouble(), strs[1].toDouble()));
	return shape;
}


//离散曲线
//？加厚度
void Equation::DescreteCurve(QVector<Bit_Point2D>& points, unsigned num)
{
	if(!shape_describe_ || num < 1)
		return ;
	InitEquation();
	points.resize(num);
	double dx = 0;
	if(num > 1)
		dx = (x_max_ - x_min_) / (num-1);
	double x = x_min_;
	for(int i=0; i<num; ++i)
	{
		points[i].Set_x(x);
		points[i].Set_y(CountY(x));
		x += dx;
	}
}

CurveEquation::CurveEquation(const ShapeDescribe* shape_describe)
	: Equation(shape_describe)
	, A_(0)
	, B_(0)
	, C_(0)
	, D_(0)
	, E_(0)
	, F_(0)
{

}


void CurveEquation::InitEquation()
{
	A_ = 0;
	B_ = 0;
	C_ = 0;
	D_ = 0;
	E_ = 0;
	F_ = 0;

	Bit_Point2D datum_point = shape_describe_->get_datum_point();
	double x = datum_point.Get_x();
	double y = datum_point.Get_y();
	const ConeDescribe* cone = dynamic_cast<const ConeDescribe*>(shape_describe_);
	const CylinderDescribe* cylinder = dynamic_cast<const CylinderDescribe*>(shape_describe_);
	const OvalDescribe* oval = dynamic_cast<const OvalDescribe*>(shape_describe_);
	if(cone)
	{
		double r1 = cone->get_left_r();
		double r2 = cone->get_right_r();
		double l = cone->get_length();
		E_ = -1;
		D_ = (r2 - r1) / l;
		F_ =  y + r2 - (x+l) * D_;
		x_min_ = x;
		x_max_ = x + l;
	}
	else if(cylinder)
	{
		double r1 = cylinder->get_r();
		double r2 = cylinder->get_r();
		double l = cylinder->get_length();
		E_ = -1;
		D_ = (r2 - r1) / l;
		F_ =  y + r2 - (x+l) * D_;
		x_min_ = x;
		x_max_ = x + l;
	}
	else if(oval)
	{
		double r1 = oval->get_left_half_height();
		double r2 = oval->get_right_half_height();
		double R = oval->get_r();
		double length = oval->get_length();
		Bit_Point2D p1(x, y+r1), p2(x+length, y+r2);
		Bit_Point2D v(p2-p1);
		ShapeDescribe::VNormalize(v);
		v = ShapeDescribe::RotateV(v, -90);
		double lv = sqrt(pow(R, 2) - pow(ShapeDescribe::Length(p1, p2)/2, 2));
		Bit_Point2D p12 = (p2+p1)*0.5;
		std::cout << p12.Get_x() << " " << p12.Get_y() << " " << lv << std::endl;
		Bit_Point2D Center(p12 + v * lv);
		double a = Center.Get_x();
		double b = Center.Get_y();
		A_ = 1;
		B_ = 1;
		C_ = 0;
		D_ = -2*a;
		E_ = -2*b;
		F_ = pow(a, 2) + pow(b, 2) - pow(R, 2);
		x_min_ = x;
		x_max_ = x+length;
	}
}

double CurveEquation::CountY(double x) const
{
	if(B_ == 0)
	{
		if(C_ * x - E_ == 0)
		{
			return 0;
		}
		else
		{
			return - (A_*pow(x, 2)+D_*x+F_) / (C_*x + E_);
		}
	}
	return (-C_*x-E_+sqrt(pow(C_*x+E_, 2)-4*B_*(F_+D_*x+A_*pow(x, 2)))) / (2 * B_);
}

//计算体积
double CurveEquation::CountVolume() const
{
	return 0;
}

double CurveEquation::CountVolume(double left_h, double right_h) const
{
	return 0;
}
double CurveEquation::CountVolume(double left_h_1, double right_h_1, double left_h_2, double right_h_2) const
{
	Q_ASSERT_X(x_max_ != x_min_, "CurveEquation::CountVolume", "x_max == x_min");

	return 0;
}

LineEquation::LineEquation(const ShapeDescribe* shape_describe)
	: Equation(shape_describe)
	, a_(0)
	, b_(0)
{
	InitEquation();
}
void LineEquation::InitEquation()
{
	Bit_Point2D datum_point = shape_describe_->get_datum_point();
	double x = datum_point.Get_x();
	double y = datum_point.Get_y();
	const ConeDescribe* cone = dynamic_cast<const ConeDescribe*>(shape_describe_);
	const CylinderDescribe* cylinder = dynamic_cast<const CylinderDescribe*>(shape_describe_);
	if(cone)
	{
		double r1 = cone->get_left_r();
		double r2 = cone->get_right_r();
		double l = cone->get_length();
		a_ = tan((r2-r1)/l);
		b_ = r1 - a_ * x;
		x_min_ = x;
		x_max_ = x + l;
	}
	else if(cylinder)
	{
		double r = cylinder->get_r();
		double l = cylinder->get_length();
		a_ = 0;
		b_ = r;
		x_min_ = x;
		x_max_ = x + l;
	}
}
double LineEquation::CountY(double x) const
{
	return a_*x+b_;
}

double LineEquation::CountVolume() const
{
	if(a_ == 0)
	{
		return M_PI * pow(b_, 2) * (x_max_ - x_min_);
	}
	return M_PI * (pow((a_ * x_max_ + b_), 3) - pow((a_*x_min_ + b_), 3)) / (3 * a_);
}
double LineEquation::CountVolume(double left_h, double right_h) const
{
	double c = x_min_;
	double d = x_max_;
	double h1 = left_h;
	double h2 = right_h;
	if(a_ == 0)
	{
		return - (1/3) * M_PI *(c-d)*(3*pow(b_, 2)+3*b_*(h1+h2) + pow(h1, 2) + h1*h2 + pow(h2, 2));
	}
	return M_PI * (c-d)*(pow((a_*d+b_+h2), 3) - pow((a_*c+b_+h1), 3)) / (3*(a_*(c-d)+h1-h2));
}
double LineEquation::CountVolume(double left_h_1, double right_h_1, double left_h_2, double right_h_2) const
{
	return CountVolume(left_h_2, right_h_2) - CountVolume(left_h_1, right_h_1);
}



CircleEquation::CircleEquation(const ShapeDescribe* shape_describe)
	: Equation(shape_describe)
	, a_(0)
	, b_(0)
	, r_(0)
{
	InitEquation();
}
//计算体积
double CircleEquation::CountVolume() const
{
	return 0;
}
double CircleEquation::CountVolume(double left_h, double right_h) const
{
	return 0;
}
double CircleEquation::CountVolume(double left_h_1, double right_h_1, double left_h_2, double right_h_2) const
{
	return 0;
}

void CircleEquation::InitEquation()
{
	Bit_Point2D datum_point = shape_describe_->get_datum_point();
	double x = datum_point.Get_x();
	double y = datum_point.Get_y();
	const OvalDescribe* oval = dynamic_cast<const OvalDescribe*>(shape_describe_);
	if(oval)
	{
		double r1 = oval->get_left_half_height();
		double r2 = oval->get_right_half_height();
		double R = oval->get_r();
		double length = oval->get_length();
		Bit_Point2D p1(x, y+r1), p2(x+length, y+r2);
		Bit_Point2D v(p2-p1);
		ShapeDescribe::VNormalize(v);
		v = ShapeDescribe::RotateV(v, -90);
		double lv = sqrt(pow(R, 2) - pow(ShapeDescribe::Length(p1, p2)/2, 2));
		Bit_Point2D p12 = (p2+p1)*0.5;
		Bit_Point2D Center(p12 + v * lv);
		a_ = Center.Get_x();
		b_ = Center.Get_y();
		r_ = R;
		x_min_ = x;
		x_max_ = x+length;
	}
}
double CircleEquation::CountY(double x) const
{
	return b_ + sqrt(pow(r_, 2) - pow(x-a_, 2));
}