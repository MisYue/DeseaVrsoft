#include "warheaddataentity.h"
#include "WarheadPower.h"
#include "WarheadStructure.h"
#include "WarheadExtraProperty.h"

WarheadDataEntity::WarheadDataEntity()
	: power_(new WarheadPower)
	, structure_(new WarheadStructure)
	, extra_property_(new WarheadExtraProperty)
{

}
WarheadDataEntity::WarheadDataEntity(WarheadStructure* structure)
	: power_(new WarheadPower)
	, structure_(structure)
	, extra_property_(new WarheadExtraProperty)
{

}

WarheadDataEntity::~WarheadDataEntity()
{
	delete power_;
	delete structure_;
	delete extra_property_;
}
