#include "warhead_node.h"
#include <MaterialLib/materiallib.h>

WarheadNode::WarheadNode()
{
	name_ = "New Node";
	guid_ = QUuid::createUuid().toString();
}

WarheadNode::~WarheadNode()
{

}

WarheadMassNode::WarheadMassNode()
	: volume_(0)
	, mass_(0)
	, material_(0)
{

}

WarheadMassNode::~WarheadMassNode()
{

}
//void WarheadMassNode::set_material_sign(const MaterialSign& material_sign)
//{
//	material_sign_ = material_sign;
//}

void WarheadMassNode::set_shape_describe(const ShapeDescribe* shape_describe)
{
	shape_describe_ = shape_describe;
}

void WarheadMassNode::set_thickness(const ShapeThickness& thickness)
{
	thickness_ = thickness;
}

void WarheadMassNode::CountMass()
{
	//访问材料库，获取材料密度
	double density = 0;
	const Material* material = 0;
	Bit_UnitSystem material_us;
	if(material)
	{
		density = material->get_density();
		material_us = material->get_us();
		//单位制转换
		Bit_UnitSystem current_us = shape_describe_->get_us();
		double current_density_coefficient = current_us.Get_DensityCoefficient();
		double material_density_coefficient = material_us.Get_DensityCoefficient();
		density = density * (material_density_coefficient / current_density_coefficient);
		mass_ = volume_ * density;
	}
}

WarheadEndCap::WarheadEndCap(const Bit_UnitSystem& us, double r, double pos_x, double length)
{
	shape_describe_ = new CylinderDescribe(us, r, length);
	const_cast<ShapeDescribe*>(shape_describe_.get())->set_datum_point(Bit_Point2D(pos_x, 0));
}
void WarheadEndCap::set_lenght(double length)
{
	dynamic_cast<CylinderDescribe*>(const_cast<ShapeDescribe*>(shape_describe_.get()))->set_length(length);
}
void WarheadEndCap::set_pos_x(double pos_x)
{
	dynamic_cast<CylinderDescribe*>(const_cast<ShapeDescribe*>(shape_describe_.get()))->set_datum_point(Bit_Point2D(pos_x, 0));
}
double WarheadEndCap::get_pos_x() const
{
	return dynamic_cast<CylinderDescribe*>(const_cast<ShapeDescribe*>(shape_describe_.get()))->get_datum_point().Get_x();
}
void WarheadEndCap::set_r(double r)
{
	dynamic_cast<CylinderDescribe*>(const_cast<ShapeDescribe*>(shape_describe_.get()))->set_r(r);
}
double WarheadEndCap::get_r() const
{
	return dynamic_cast<CylinderDescribe*>(const_cast<ShapeDescribe*>(shape_describe_.get()))->get_r();
}

void WarheadEndCap::CountVolume()
{
	volume_ = M_PI * pow(get_r(), 2) * get_length();
}
