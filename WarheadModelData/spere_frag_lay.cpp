#include "spere_frag_lay.h"
#include <BIT2DComputeSupport/Bit_2DCompute.h>

//向量归一
void VNormalize(Bit_Point2D& v)
{
	double x = v.Get_x();
	double y = v.Get_y();
	double l2 = sqrt(pow(x, 2) + pow(y, 2));
	x /= l2;
	y /= l2;
	v.Set_x(x);
	v.Set_y(y);
}

Bit_Point2D RotateV(const Bit_Point2D& v, double degrees)
{
	double rad = degrees / (180/M_PI);
	double v_x = v.Get_x();
	double v_y = v.Get_y();
	double cos_rad = cos(rad);
	double sin_rad = sin(rad);
	return Bit_Point2D(v_x * cos_rad - v_y * sin_rad, v_x * sin_rad + v_y * cos_rad);
}

void RotateP(const Bit_Point2D& center, Bit_Point2D& p, double rad)
{
	double c_x = center.Get_x();
	double c_y = center.Get_y();
	Bit_Point2D temp_p(p.Get_x()-c_x, p.Get_y()-c_y);
	temp_p = RotateV(temp_p, rad * (180/M_PI));
	p.Set_x(c_x + temp_p.Get_x());
	p.Set_y(c_y + temp_p.Get_y());
}

SphereFragLay::SphereFragLay(SphereFragmentLayer::LayoutMethod layout_method, unsigned layer_num, double r, double away_left_h, double away_right_h, const ShapeDescribe* shape)
	: layer_num_(layer_num)
	, r_(r)
	, away_left_h_(away_left_h)
	, away_right_h_(away_right_h)
	, shape_(shape)
	, left_h_(0)
	, right_h_(0)
	, frag_num_(0)
	, layout_method_(layout_method)
{
}

void SphereFragLay::Lay(Fragments& fragments, QList<QList<double> >& normal_angles, QList<double>& frags_circle_radius)
{
	fragments_ = &fragments;
	frags_circle_radius_ = &frags_circle_radius;
	normal_angles_ = &normal_angles;
	frag_num_ = 0;
	UpdateVar();
	//布设每一层
	for(unsigned i=0; i<layer_num_; ++i)
		LayPerLayer(i);
}


OvalShapeLay::OvalShapeLay(SphereFragmentLayer::LayoutMethod layout_method, unsigned layer_num, double r, double away_left_h, double away_right_h, const ShapeDescribe* shape)
	: SphereFragLay(layout_method, layer_num, r, away_left_h, away_right_h, shape), dx_(1)
{

}

void OvalShapeLay::LayPerLayer(unsigned layer_index)
{
	fragments_->push_back(LayerFrags());
	normal_angles_->push_back(QList<double>());
	LayerFrags& layer_frags = fragments_->back();
	QList<double>& layer_normals = normal_angles_->back();
	Bit_Point2D c = FirstLayerCenter();
	if(h1_ != h2_)
	{
		while(c != Bit_Point2D(0, 0))
		{
			layer_frags.push_back(CircleFrags());
			QList<CoordinatesPosition>& frags_circle = layer_frags.back();
			frags_circle.push_back(CoordinatesPosition(c.Get_x(), c.Get_y(), 0));
			frags_circle_radius_->push_back(c.Get_y() - r_);
			layer_normals.push_back(CountNormalAngle(c));
			//单个破片对圆周的角度
			double rad = asin(r_ / (r_ + frags_circle_radius_->back())) * 2;
			//圆周布设个数
			frag_num_ += (int)(2 * M_PI / rad);
			c = NextLayerCenter(c);
		}
	}
	else
	{
		double x_1, y_1, x_2, y_2;
		double a = a_;
		double b = b_+h1_;
		double R = R_;
		x_1 = c.Get_x();
		y_1 = c.Get_y(); //b + sqrt(-pow(a, 2) + pow(r_, 2) + 2 * R * r_ + pow(R, 2) + 2 * a * x_1 - pow(x_1, 2));
		x_2 = x_1 - r_ + l_ - r_;
		y_2 = b + sqrt(-pow(a, 2) + pow(r_, 2) + 2 * R * r_  + pow(R, 2) + 2 * a * x_2 - pow(x_2, 2));
		//单个破片对圆周的角度
		double per_rad = atan(r_/(R+r_))*2;
		//第一层可布设圆周角
		Bit_2DCompute sc2d;
		double lay_rad = sc2d.ComputeAngleTwoV(Bit_Point2D(x_1-a, y_1-b), Bit_Point2D(x_2-a, y_2-b));
		//可布设个数
		int num = lay_rad / per_rad + 1;
		//布设间隔
		double space_rad = per_rad;
		if(num > 1)
			space_rad = lay_rad /(num-1);
		for(unsigned i = 0; i<num; ++i)
		{
			layer_frags.push_back(CircleFrags());
			QList<CoordinatesPosition>& frags_circle = layer_frags.back();
			frags_circle.push_back(CoordinatesPosition(c.Get_x(), c.Get_y(), 0));
			frags_circle_radius_->push_back(c.Get_y());
			layer_normals.push_back(CountNormalAngle(c));
			RotateP(Bit_Point2D(a, b), c, -space_rad);
			//单个破片对圆周的角度
			double rad = asin(r_ / (r_ + frags_circle_radius_->back())) * 2;
			//圆周布设个数
			frag_num_ += (int)(2 * M_PI / rad);
		}
	}

	h1_ += 2*r_;
	h2_ += 2 * r_;

	if(layer_index == layer_num_-1)
	{
		left_h_ = h1_ - (away_left_h_ - r1_);
		right_h_ = h2_ - (away_right_h_ - r2_);
	}
}
void OvalShapeLay::UpdateVar() 
{
	const OvalDescribe* shape = dynamic_cast<const OvalDescribe*>(shape_);
	Q_ASSERT(shape);
	double r1 = shape->get_left_half_height();
	double r2 = shape->get_right_half_height();
	double R = shape->get_r();
	double length = shape->get_length();
	Bit_Point2D datum_point = shape->get_datum_point();
	double x = datum_point.Get_x();
	double y = datum_point.Get_y();
	Bit_Point2D p1(x, y+r1), p2(x+length, y+r2);
	Bit_Point2D v(p2-p1);
	VNormalize(v);
	v = RotateV(v, -90);
	double lv = sqrt(pow(R, 2) - pow(ShapeDescribe::Length(p1, p2)/2, 2));
	Bit_Point2D p12 = (p2+p1)*0.5;
	Bit_Point2D Center(p12 + v * lv);
	R_ = R;
	a_ = Center.Get_x();
	b_ = Center.Get_y();
	l_ = length;
	h1_ = away_left_h_ - r1;
	h2_ = away_right_h_ - r2;
	x0_ = x;
	y0_ = y;
	r1_ = r1;
	r2_ = r2;

	left_h_ = 0;
	right_h_ = 0;
}

double OvalShapeLay::CountShapeY(double x)
{
	return b_ + sqrt(-pow(a_, 2) + pow(R_, 2) + 2 * a_ * x - pow(x, 2));
}
double OvalShapeLay::CountY(double x)
{
	double y1 = CountShapeY(x);
	double y2 = h1_ + (x-x0_)*(h2_-h1_)/l_;
	return y1+y2;
}
double OvalShapeLay::CountD(double x)
{
	return (h2_-h1_)/l_ + (a_-x)/sqrt(-pow(a_, 2) + pow(R_, 2) + 2 * a_ * x - pow(x, 2));
}
Bit_Point2D OvalShapeLay::CountCenter(double x)
{
	//求切线方程y=mx+n
	double y1 = CountY(x);
	double y2 = CountD(x);
	double m = - 1 / y2;
	double n = y1 + x/y2;
	Bit_Point2D v(1, m);
	VNormalize(v);
	double y = m * x + n;

	return Bit_Point2D(x, y) + v * (m<0 ? (-r_) : r_);
}
Bit_Point2D OvalShapeLay::FirstLayerCenter()
{
	for(double x = x0_, k = x0_ + l_; x < k; x += dx_)
	{
		Bit_Point2D c = CountCenter(x);
		if(c.Get_x() >= x0_+r_)
			return c;
	}
	return Bit_Point2D(0, 0);
}
Bit_Point2D OvalShapeLay::NextLayerCenter(const Bit_Point2D& c)
{
	for(double x = c.Get_x(), k = x0_ + l_ - r_; x <= k; x += dx_)
	{
		Bit_Point2D c2 = CountCenter(x);
		if(ShapeDescribe::Length(c, c2) >= 2*r_)
			return c2;
	}
	return Bit_Point2D(0, 0);
}
double OvalShapeLay::CountNormalAngle(const Bit_Point2D& pos)
{
	Bit_Point2D b2d(pos.Get_x() - a_, pos.Get_y() - b_);
	Bit_2DCompute sc2d;
	double rad = sc2d.ComputeAngleTwoV(b2d, Bit_Point2D(1, 0));
	return rad;
}

LineShapeLay::LineShapeLay(SphereFragmentLayer::LayoutMethod layout_method, unsigned layer_num, double r, double away_left_h, double away_right_h, const ShapeDescribe* shape)
	: SphereFragLay(layout_method, layer_num, r, away_left_h, away_right_h, shape)
{

}
void LineShapeLay::LayPerLayer(unsigned layer_index)
{
	//每层开始布设端点
	Bit_Point2D endpoint = datum_point_ + Bit_Point2D(0, layer_index * per_layer_h_ + away_left_h_) + RotateV(per_layer_v_, 90) * r_;

	//修正布设端点，从低到高布设
	if(away_left_h_ > away_right_h_)
	{
		endpoint = datum_point_ + Bit_Point2D(shape_->get_shape_length(), layer_index * per_layer_h_ + away_right_h_) + RotateV(per_layer_v_, -90) * r_;
	}
	endpoint = endpoint + per_layer_v_ * (per_layer_first_distance_+r_);
	//double circle_radius = first_layer_circle_radius_ + per_layer_h_*layer_index;
	double circle_radius = 0;
	fragments_->push_back(LayerFrags());
	LayerFrags& layer_frags = fragments_->back();
	normal_angles_->push_back(QList<double>());
	QList<double>& layer_normals = normal_angles_->back();
	for(unsigned i = 0; i<per_layer_num_; ++i)
	{
		layer_frags.push_back(CircleFrags());
		CircleFrags& frags_circle = layer_frags.back();
		frags_circle.push_back(CoordinatesPosition(endpoint.Get_x(), endpoint.Get_y(), 0));
		circle_radius = endpoint.Get_y()-r_;
		frags_circle_radius_->push_back(circle_radius);
		layer_normals.push_back(normal_angle_);
		//每圈布设个数
		frag_num_ += CountCircleNum(circle_radius);
		//if(layer_index>0)
		//{
		//	layer_frags.push_back(CircleFrags());
		//	CircleFrags& frags_circle = layer_frags.back();
		//	Bit_Point2D p2d(endpoint.Get_x()+sqrt(3.0)*r_, endpoint.Get_y()+r_);
		//	frags_circle.push_back(CoordinatesPosition(p2d.Get_x(), p2d.Get_y(), 0));
		//	circle_radius = p2d.Get_y()-r_;
		//	frags_circle_radius_->push_back(circle_radius);
		//	layer_normals.push_back(normal_angle_); 
		//	//每圈布设个数

		//	frag_num_ += CountCircleNum(circle_radius);
		//}
		endpoint = endpoint + per_layer_v_ * space_l_;
	}
}
void LineShapeLay::UpdateVar() 
{
	//基准点
	datum_point_ = shape_->get_datum_point();
	//计算每一层高度
	double away_dh = fabs(away_right_h_ - away_left_h_);  //左右两端高度差
	double shape_l = shape_->get_shape_length(); //形状长度
	double temp_rad = atan(away_dh/shape_l);
	per_layer_h_ = r_*2 / (cos(temp_rad));
	//每层长度
	per_layer_l_ = sqrt(pow(away_dh, 2) + pow(shape_l, 2));
	//每层方向
	per_layer_v_.Set_x(shape_l); per_layer_v_.Set_y(away_dh);
	VNormalize(per_layer_v_);
	//每层第一个球心距左端长度，沿布设方向
	per_layer_first_distance_ = r_ / tan((M_PI_2 - temp_rad)/2) - r_;
	//每层布设个数
	space_l_ = 2*r_;
	//space_l_ = 2*sqrt(3.0)*r_;
	//space_l_ = 2 * 2*r_*cos(M_PI/6-temp_rad);
	double d_num = (per_layer_l_ - per_layer_first_distance_) / space_l_;
	per_layer_num_ = d_num;

	if(per_layer_num_ > 1)
		space_l_ += ((per_layer_l_ - per_layer_first_distance_) - per_layer_num_*space_l_) / (per_layer_num_-1);
	double away_ddh = fabs(away_left_h_ - away_right_h_) / per_layer_l_;
	first_layer_circle_radius_ = away_left_h_ + (per_layer_first_distance_+r_) * away_ddh;
	//修正布设方向及第一层第一圈的半径
	if(away_left_h_ > away_right_h_)
	{
		per_layer_v_.Set_x(-per_layer_v_.Get_x());
		first_layer_circle_radius_ = away_right_h_ + (per_layer_first_distance_+r_) * away_ddh;
	}
	d_circle_radius_ = space_l_ * away_ddh;

	left_h_ = per_layer_h_ * layer_num_;
	right_h_ = per_layer_h_ * layer_num_;

	Bit_2DCompute sc2d;
	double coef = per_layer_v_.Get_x() < 0 ? -1 : 1;
	normal_angle_ = sc2d.ComputeAngleTwoV(RotateV(per_layer_v_ * coef, 90), Bit_Point2D(1, 0));
}