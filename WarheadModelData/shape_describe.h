#pragma once

#include "warhead_model_data_global.h"

#include <BIT2DCSSupport/Bit_2DCSWithExpAndUS.h>
#ifdef pi
#undef pi
#endif
#include <osg/Referenced>
#include <osg/ref_ptr>

#include <QtCore>

//֧�ֳ˷�
extern WARHEADMODELDATA_EXPORT Bit_Point2D operator * (const Bit_Point2D& p2d, double d);

enum ShapeType
{
	kCone,
	kCylinder,
	kOval,

};
//��״����
class WARHEADMODELDATA_EXPORT ShapeDescribe : public osg::Referenced
{
public:
	ShapeDescribe(const Bit_UnitSystem& us, const Bit_Point2D& datum_point = Bit_Point2D()) 
		: datum_point_(datum_point)
		, shape_length_(0)
		, shape_left_half_height_(0)
		, shape_right_half_height_(0)
		, us_(us)
	{}
	//��׼��
	void set_datum_point(const Bit_Point2D& datum_point) { datum_point_ = datum_point; }
	Bit_Point2D get_datum_point() const { return datum_point_; }
	void Translate(double dx) { datum_point_.Set_x(datum_point_.Get_x() + dx); }
	//��״����
	double get_shape_length() const { return shape_length_; }
	//��״�߶�
	double get_shape_left_half_height() const { return shape_left_half_height_; }
	double get_shape_right_half_height() const { return shape_right_half_height_; }
	//��ȡ��״����
	ShapeType get_shape_type() const { return shape_type_; }
	//��ȡ��λ��
	Bit_UnitSystem get_us() const { return us_; }
	//����==�����
	bool operator == (const ShapeDescribe& shape) const
	{
		return (shape_type_ == shape.shape_type_ 
			&& datum_point_ == shape.datum_point_ 
			&& shape_length_ == shape.shape_length_
			&& shape_left_half_height_ == shape.shape_left_half_height_
			&& shape_right_half_height_ == shape.shape_right_half_height_);
	}

	//��ȡ��״���������б�
	virtual QString GetShapeDescribe() const = 0;
	//�ж���״�����Ƿ���ͬ
	bool IsEqual(const ShapeDescribe* shape) const;

	//�������
	virtual double CountVolume(double left_h, double right_h) const = 0;

	//��״��������
	static ShapeDescribe* CreateShape(const Bit_UnitSystem& us, ShapeType type, const QString& describe);
	//������һ
	static void VNormalize(Bit_Point2D& v);
	//��ת��������
	static Bit_Point2D RotateV(const Bit_Point2D& v, double degrees);
	//��������
	static double Length(const Bit_Point2D& p1, const Bit_Point2D& p2);

protected:
	Bit_Point2D datum_point_;	//��׼��
	//���±����ڶ����֮�����ʹ��
	double shape_length_;	//��״����
	double shape_left_half_height_; //��״��˰��
	double shape_right_half_height_; //��״�Ҷ˰��

	ShapeType shape_type_;
	//��λ��
	Bit_UnitSystem us_;
};

//Բ̨
class WARHEADMODELDATA_EXPORT ConeDescribe : public ShapeDescribe
{
public:
	ConeDescribe(const Bit_UnitSystem& us, double left_r = 0, double right_r = 0, double length = 0) 
		: left_r_(left_r), right_r_(right_r), length_(length)
		, ShapeDescribe(us)
	{
		shape_type_ = kCone;
		shape_length_ = length_;
		shape_left_half_height_ = left_r_;
		shape_right_half_height_ = right_r_;
	}
	//��˰뾶
	void set_left_r(double r) { left_r_ = r; shape_left_half_height_ = left_r_;}
	double get_left_r() const { return left_r_; }
	//�Ҷ˰뾶
	void set_right_r(double r) { right_r_ = r; shape_right_half_height_ = right_r_; }
	double get_right_r() const { return right_r_; }
	//����
	void set_length(double length) { length_ = length; shape_length_ = length_; }
	double get_length() const { return length_; }

	//����==�����
	bool operator == (const ConeDescribe& shape) const
	{
		return (shape_type_ == shape.shape_type_ 
			&& datum_point_ == shape.datum_point_ 
			&& length_ == shape.length_
			&& left_r_ == shape.left_r_
			&& right_r_ == shape.right_r_);
	}

	//��ȡ��״���������б�
	virtual QString GetShapeDescribe() const
	{
		QString result = QString("%1,%2,%3,%4,%5")
			.arg(datum_point_.Get_x())
			.arg(datum_point_.Get_y())
			.arg(left_r_)
			.arg(right_r_)
			.arg(length_);
		return result;
	}
	//�������
	virtual double CountVolume(double left_h, double right_h) const
	{
		double _r1 = left_r_ + left_h;
		double _r2 = right_r_ + right_h;
		double v =  M_PI * length_ * (pow(_r1, 2)+pow(_r2, 2) + _r1*_r2) / 3.0;
		return v;
	}
protected:
	double left_r_;
	double right_r_;
	double length_;
};

//Բ��
class WARHEADMODELDATA_EXPORT CylinderDescribe : public ShapeDescribe
{
public:
	CylinderDescribe(const Bit_UnitSystem& us, double r = 0, double length = 0) : r_(r), length_(length), ShapeDescribe(us)
	{
		shape_type_ = kCylinder;
		shape_length_ = length_;
		shape_left_half_height_ = r_;
		shape_right_half_height_ = r_;
	}
	//�뾶
	void set_r(double r) { r_ = r; shape_left_half_height_ = r_; shape_right_half_height_ = r_; }
	double get_r() const { return r_; }
	//����
	void set_length(double length) { length_ = length; shape_length_ = length_; }
	double get_length() const { return length_; }

	//��ȡ��״���������б�
	virtual QString GetShapeDescribe() const
	{
		QString result = QString("%1,%2,%3,%4")
			.arg(datum_point_.Get_x())
			.arg(datum_point_.Get_y())
			.arg(r_)
			.arg(length_);
		return result;
	}

	//����==�����
	bool operator == (const CylinderDescribe& shape) const
	{
		return (shape_type_ == shape.shape_type_ 
			&& datum_point_ == shape.datum_point_ 
			&& length_ == shape.length_
			&& r_ == shape.r_);
	}
	//�������
	virtual double CountVolume(double left_h, double right_h) const
	{
		double _r1 = r_ + left_h;
		double _r2 = r_ + right_h;
		return (M_PI/3) * length_ * (pow(_r1, 2)+pow(_r2, 2) + _r1*_r2);
	}
protected:
	double r_;
	double length_;
};

//����
class WARHEADMODELDATA_EXPORT OvalDescribe : public ShapeDescribe
{
public:
	OvalDescribe(const Bit_UnitSystem& us, double left_half_height = 0, double right_half_height = 0, double length = 0, double r = 0) 
		: left_half_height_(left_half_height), right_half_height_(right_half_height), length_(length), r_(r), ShapeDescribe(us)
	{
		shape_type_ = kOval;
		shape_length_ = length_;
		shape_left_half_height_ = left_half_height_;
		shape_right_half_height_ = right_half_height_;
	}
	//�߶�
	void set_left_half_height(double h) { left_half_height_ = h; shape_left_half_height_ = left_half_height_; }
	double get_left_half_height() const { return left_half_height_; }
	void set_right_half_height(double h) { right_half_height_ = h; shape_right_half_height_ = right_half_height_; }
	double get_right_half_height() const { return right_half_height_; }
	//�뾶
	void set_r(double r) { r_ = r; }
	double get_r() const { return r_; }
	//����
	void set_length(double length) { length_ = length; shape_length_ = length_; }
	double get_length() const { return length_; }

	//��ȡ��״���������б�
	virtual QString GetShapeDescribe() const
	{
		QString result = QString("%1,%2,%3,%4,%5,%6")
			.arg(datum_point_.Get_x())
			.arg(datum_point_.Get_y())
			.arg(left_half_height_)
			.arg(right_half_height_)
			.arg(r_)
			.arg(length_);
		return result;
	}

	//����==�����
	bool operator == (const OvalDescribe& shape) const
	{
		return (shape_type_ == shape.shape_type_ 
			&& datum_point_ == shape.datum_point_ 
			&& length_ == shape.length_
			&& left_half_height_ == shape.left_half_height_ 
			&& right_half_height_ == shape.right_half_height_
			&& r_ == shape.r_);
	}
	//�������
	virtual double CountVolume(double left_h, double right_h) const
	{ 
		//��ȱ�ĸ�
		double  h_1 = r_ - sqrt(pow(r_, 2) - (pow(length_, 2) + pow(right_half_height_ - left_half_height_, 2))/4);
		//��ȱ�����
		double v_1 = 2 * (M_PI/3) * (3*r_ - h_1) * pow(h_1, 2);
		//Բ̨���
		double _r1 = left_half_height_ + left_h;
		double _r2 = right_half_height_ + right_h;
		double v_2 = (M_PI/3) * length_ * (pow(_r1, 2)+pow(_r2, 2) + _r1*_r2);
		return v_1 + v_2;
	}

protected:
	double left_half_height_;
	double right_half_height_;
	double length_;
	double r_;
};

//����
class WARHEADMODELDATA_EXPORT Equation
{
public:
	Equation(const ShapeDescribe* shape_describe) : x_min_(0), x_max_(0) , shape_describe_(shape_describe) {}
	virtual ~Equation() {}
	//��ɢ����
	void DescreteCurve(QVector<Bit_Point2D>& points, unsigned num);
	//�������
	virtual double CountVolume() const = 0;
	virtual double CountVolume(double left_h, double right_h) const = 0;
	virtual double CountVolume(double left_h_1, double right_h_1, double left_h_2, double right_h_2) const = 0;
	virtual void InitEquation() = 0;
protected:
	osg::ref_ptr<const ShapeDescribe> shape_describe_;
	virtual double CountY(double x) const = 0;
	double x_min_, x_max_;
};
//���߷��� AX^2+BY^2+CXY+DX+EY+F=0
class WARHEADMODELDATA_EXPORT CurveEquation : public Equation
{
public:
	CurveEquation(const ShapeDescribe* shape_describe);
	//�������
	virtual double CountVolume() const;
	virtual double CountVolume(double left_h, double right_h) const;
	virtual double CountVolume(double left_h_1, double right_h_1, double left_h_2, double right_h_2) const;
	virtual void InitEquation();
protected:
	double A_, B_, C_, D_, E_, F_;
	virtual double CountY(double x) const;
};

//ֱ�߷��� y = ax+b

class WARHEADMODELDATA_EXPORT LineEquation : public Equation
{
public:
	LineEquation(const ShapeDescribe* shape_describe);
	//�������
	virtual double CountVolume() const;
	virtual double CountVolume(double left_h, double right_h) const;
	virtual double CountVolume(double left_h_1, double right_h_1, double left_h_2, double right_h_2) const;
	virtual void InitEquation();
protected:
	double a_, b_;
	virtual double CountY(double x) const;
};

//Բ���� 
class WARHEADMODELDATA_EXPORT CircleEquation : public Equation
{
public:
	CircleEquation(const ShapeDescribe* shape_describe);
	//�������
	virtual double CountVolume() const;
	virtual double CountVolume(double left_h, double right_h) const ;
	virtual double CountVolume(double left_h_1, double right_h_1, double left_h_2, double right_h_2) const;
	virtual void InitEquation();
protected:
	double a_, b_, r_;
	virtual double CountY(double x) const;
};