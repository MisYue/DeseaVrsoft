#pragma once

#include "dbmdata_global.h"
#include <QtCore>

class FieldInfo;
class DBMDATA_EXPORT FieldValue
{
public:
	FieldValue(const QVariant& value, const FieldInfo* field_info);
	virtual ~FieldValue(void);

	const FieldInfo* get_field_info() const { return field_info_; }
	const QVariant& get_value() const { return value_; }

	bool IsExpandType();

protected:
	QVariant value_;	//Öµ
	const FieldInfo* field_info_;		//×Ö¶ÎÐÅÏ¢
};

