#include "WarheadExtraProperty.h"


WarheadExtraProperty::WarheadExtraProperty(void)
	: id_(0)
	, guid_(QUuid::createUuid().toString())
	, share_(true)
	, name_("New Warhead")
	, service_start_date_(QDate::currentDate())
	, service_end_date_(QDate::currentDate())
	, create_time_(QDateTime::currentDateTime())
	, update_time_(QDateTime::currentDateTime())
{
}


WarheadExtraProperty::~WarheadExtraProperty(void)
{
}
