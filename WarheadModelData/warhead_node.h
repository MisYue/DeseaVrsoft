
#pragma once
#include "warhead_model_data_global.h"
#include "shape_describe.h"
#include <QtCore>

class WarheadModel;
class Material;

class WARHEADMODELDATA_EXPORT WarheadNode
{
public:
	WarheadNode();
	virtual ~WarheadNode();
	QString get_guid() const { return guid_; }
	QString get_name() const { return name_; }
	void set_name(const QString& name) { name_ = name; }
protected:
	QString name_;
	QString guid_;
};


//定义形状厚度类型，有歧义
enum ThicknessType
{
	kNo,	//无意义
	kUp,	//沿形状曲线向上延伸
	kDown,	//沿形状曲线向下延伸
};
struct ShapeThickness
{
	ThicknessType type; //厚度类型
	double left; //左端厚度
	double right; //右端厚度

	ShapeThickness(ThicknessType _type = kNo, double _left = 0, double _right = 0) : left(_left), right(_right), type(_type) {}
	bool operator == (const ShapeThickness& thickness) const
	{
		return (thickness.left == left
			&& thickness.right == right
			&& thickness.type == type);
	}
	bool operator != (const ShapeThickness& thickness) const
	{
		return !((*this) == thickness);
	}
};

class WARHEADMODELDATA_EXPORT WarheadMassNode : public WarheadNode
{
public:
	WarheadMassNode();
	~WarheadMassNode();
	//材料，设置材料时会自动计算质量
	void set_material(const Material* material) { material_ = material; }
	const Material* get_material() const { return material_; }
	//void set_material_sign(const MaterialSign& material_sign);
	//MaterialSign get_material_sign() const { return material_sign_; }
	//形状描述，设置形状描述时，会自动计算体积和质量
	void set_shape_describe(const ShapeDescribe* shape_describe);
	const ShapeDescribe* get_shape_describe() const { return shape_describe_; }

	double get_volume() const { return volume_; }
	//质量
	void CountMass();
	double get_mass() const { return mass_; }
	//厚度，设置厚度时，会自动计算体积和质量
	void set_thickness(const ShapeThickness& thickness);
	ShapeThickness get_thickness() const { return thickness_; }


protected:
	//MaterialSign material_sign_; //材料标识
	const Material* material_;	//材料
	double volume_; //体积
	double mass_; //质量
	osg::ref_ptr<const ShapeDescribe> shape_describe_; //形状描述对象
	ShapeThickness thickness_;
};


//定义段盖类型，端盖均为圆柱形，
class WARHEADMODELDATA_EXPORT WarheadEndCap : public WarheadMassNode
{
	friend WarheadModel;
public:
	WarheadEndCap(const Bit_UnitSystem& us, double r, double pos_x, double length);
	double get_length() const { return shape_describe_->get_shape_length(); }
	void set_lenght(double length);
	double get_pos_x() const ;
	double get_r() const;
	//体积
	void CountVolume();
private:
	void set_pos_x(double pos_x);
	void set_r(double r);
	Bit_UnitSystem us_;
};

//定义起爆点类型
class  WarheadFirePoint : public WarheadNode
{
	friend WarheadModel;
public:
	WarheadFirePoint(int id) : id_(id){}
	void Translate(double dx) { pos_.Set_x(pos_.Get_x()+dx); }
	void set_pos(const Bit_Point2D& pos) { pos_ = pos; }
	Bit_Point2D get_pos() const { return pos_; }
	int get_id() const { return id_; }
protected:
	Bit_Point2D pos_;
	int id_;
};