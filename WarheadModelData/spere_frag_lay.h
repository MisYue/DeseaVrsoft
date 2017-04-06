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
	double circle_lay_space_; //�����Ų����
	double r_;
	const ShapeDescribe* shape_;
	Fragments* fragments_;
	QList<double>* frags_circle_radius_;
	QList<QList<double> >* normal_angles_;
	SphereFragmentLayer::LayoutMethod layout_method_;

	int CountCircleNum(double circle_r)
	{
		//������Ƭ��Բ�ܵĽǶ�
		double rad = asin(r_ / (r_ + circle_r)) * 2;
		//Բ�ܲ������
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
	double per_layer_h_; //ÿһ��߶�
	unsigned per_layer_num_; //ÿһ�����
	double space_l_;	//�������
	Bit_Point2D datum_point_; //��״��׼��

	double per_layer_first_distance_;	//ÿһ���һ����Ƭ����˵ĳ��ȣ��ز��跽��
	Bit_Point2D per_layer_v_; //ÿһ��ķ���
	double per_layer_l_; //ÿ�㳤��
	double first_layer_circle_radius_; //��һȦ����뾶
	double d_circle_radius_; //ÿ�㲼��뾶����
	double normal_angle_;
};