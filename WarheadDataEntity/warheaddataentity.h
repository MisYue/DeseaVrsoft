#ifndef WARHEADDATAENTITY_H
#define WARHEADDATAENTITY_H

#include "Entity.h"
#include <WarheadDataEntity/WarheadPower.h>
#include <WarheadDataEntity/WarheadExtraProperty.h>
#include <WarheadDataEntity/WarheadStructure.h>


class WARHEADDATAENTITY_EXPORT WarheadDataEntity : public Entity
{
public:
	WarheadDataEntity();
	WarheadDataEntity(WarheadStructure* structure);
	~WarheadDataEntity();

	WarheadPower* get_power() { return power_; }
	const WarheadPower* get_power() const { return power_; }
	WarheadStructure* get_structure() { return structure_; }
	const WarheadStructure* get_structure() const { return structure_; }
	WarheadExtraProperty* get_extra_property() { return extra_property_; }
	const WarheadExtraProperty* get_extra_property() const { return extra_property_; }

protected:
	WarheadPower* power_;	//威力
	WarheadStructure* structure_;	//结构
	WarheadExtraProperty* extra_property_;	//附加属性
};

#endif // WARHEADDATAENTITY_H
