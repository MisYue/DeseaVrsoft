#pragma once
#include "material.h"

class MATERIALLIB_EXPORT ChargeMaterial :
	public Material
{
public:
	ChargeMaterial();

	void set_heat(double heat) { heat_ = heat; }
	double get_heat() const { return heat_; }
	double get_heat(const Bit_UnitSystem& us) const;

	void set_pressure(double pressure) { pressure_ = pressure; }
	double get_pressure() const { return pressure_; }
	double get_pressure(const Bit_UnitSystem& us) const;

	void set_velocity(double velocity) { velocity_ = velocity; }
	double get_velocity() const { return velocity_; }
	double get_velocity(const Bit_UnitSystem& us) const;
protected:
	double heat_;	//±¨»»
	double pressure_;	//±¨—π
	double velocity_;	//±¨ÀŸ
};

