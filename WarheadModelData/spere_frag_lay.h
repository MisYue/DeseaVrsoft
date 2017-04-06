#pragma once
#include "warhead_fragment_layer.h"

class SphereFragLay
{
public:
	SphereFragLay(SphereFragmentLayer::LayoutMethod layout_method, unsigned layer_num, double r, double away_left_h, double away_right_h, const ShapeDescribe* shape);
	double get_thickness_left() const { return left_h_; }
	double get_thickess_right() const { return right_h_; }
	unsigned get_frag_num() const { return frag_num_; }
	void set_circle_lay_space(double rad) { circle_lay_space_ = rad; }
	virtual void Lay(Fragments& fragments, QList<QList<double> >& normal_angles, QList<double>& frags_circle_radius);
	virtual void LayPerLayer(unsigned layer_index) = 0;
	virtual void UpdateVar() {}
protected:
	double away_left_h_;
	double away_right_h_;
	double left_h_;
	double right_h_;
	unsigned frag_num_;
	unsigned layer_num_;
	double circle_lay_space_; //周向排布间隔
	double r_;
	const ShapeDescribe* shape_;
	Fragments* fragments_;
	QList<double>* frags_circle_radius_;
	QList<QList<double> >* normal_angles_;
	SphereFragmentLayer::LayoutMethod layout_method_;

	int CountCircleNum(double circle_r)
	{
		//单个破片对圆周的角度
		double rad = asin(r_ / (r_ + circle_r)) * 2;
		//圆周布设个数
		int num = 2 * M_PI / (rad+circle_lay_space_);
		return num;
	}
};

class OvalShapeLay : public SphereFragLay
{
public:
	OvalShapeLay(SphereFragmentLayer::LayoutMethod layout_method, unsigned layer_num, double r, double away_left_h, double away_right_h, const ShapeDescribe* shape);
	virtual void LayPerLayer(unsigned layer_index);
	virtual void UpdateVar();
protected:
	double dx_;
	double R_, h1_, h2_, l_, a_, b_, x0_, y0_;
	double r1_, r2_;
	double CountShapeY(double x);
	double CountY(double x);
	double CountD(double x);
	Bit_Point2D CountCenter(double x);
	Bit_Point2D FirstLayerCenter();
	Bit_Point2D NextLayerCenter(const Bit_Point2D& c);
	double CountNormalAngle(const Bit_Point2D& pos);
};

class LineShapeLay : public SphereFragLay
{
public:
	LineShapeLay(SphereFragmentLayer::LayoutMethod layout_method, unsigned layer_num, double r, double away_left_h, double away_right_h, const ShapeDescribe* shape);
	virtual void LayPerLayer(unsigned layer_index);
	virtual void UpdateVar();
protected:
	double per_layer_h_; //每一层高度
	unsigned per_layer_num_; //每一层个数
	double space_l_;	//间隔长度
	Bit_Point2D datum_point_; //形状基准点

	double per_layer_first_distance_;	//每一层第一个破片距左端的长度，沿布设方向
	Bit_Point2D per_layer_v_; //每一层的方向
	double per_layer_l_; //每层长度
	double first_layer_circle_radius_; //第一圈布设半径
	double d_circle_radius_; //每层布设半径增量
	double normal_angle_;
};