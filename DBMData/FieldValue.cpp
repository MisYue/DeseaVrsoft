#include "FieldValue.h"


FieldValue::FieldValue(const QVariant& value, const FieldInfo* field_info)
	: field_info_(field_info)
{
}


FieldValue::~FieldValue(void)
{
}
