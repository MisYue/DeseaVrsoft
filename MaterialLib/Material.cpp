#include "Material.h"
#include <BITUnitsSupport/Bit_USTransform.h>

double Material::get_density(const Bit_UnitSystem& us) const
{
	Bit_USTransform ust;
	return ust.TransformValue(us_, us, density_, Density);
}