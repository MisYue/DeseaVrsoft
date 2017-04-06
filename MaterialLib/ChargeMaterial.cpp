#include "ChargeMaterial.h"
#include <BITUnitsSupport/Bit_USTransform.h>
#include <BasicTool/expandqtcore.h>

ChargeMaterial::ChargeMaterial() : heat_(0), pressure_(0), velocity_(0)
{
}
double ChargeMaterial::get_heat(const Bit_UnitSystem& us) const
{
	Bit_USTransform ust;
	return ust.TransformValue(us_, us, heat_, Force);
}
double ChargeMaterial::get_pressure(const Bit_UnitSystem& us) const
{
	Bit_USTransform ust;
	return ust.TransformValue(us_, us, pressure_, Pressure);
}

double ChargeMaterial::get_velocity(const Bit_UnitSystem& us) const
{
	Bit_USTransform ust;
	return ust.TransformValue(us_, us, velocity_, Velocity);
}

