#pragma once

#include "dbmdata_global.h"
#include <QtCore>

class Table;
class DBMDATA_EXPORT Record
{
public:
	Record(void);
	virtual ~Record(void);

	QVariant GetFieldValue(const QString& field_name) const;
	QVariant GetFieldValue(int field_index) const;

	void SetFieldValue(const QString& field_name, const QVariant& field_value);
	void SetFieldValue(int field_index, const QVariant& field_value);

protected:
	Table* table_;
};

