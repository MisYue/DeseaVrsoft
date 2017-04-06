#pragma once
#include "dbmdata_global.h"
#include <QtCore>


class FieldValue;
class DBMDATA_EXPORT Result
{
public:
	Result(void);
	virtual ~Result(void);

	void Reserve(int size) { values_.reserve(size); }

	int GetFiledValueNum() const { return values_.size(); }

	void AddFieldValue(const FieldValue* value)
	{
		values_.push_back(value);
	}
	const FieldValue* Value(int index) const
	{
		if(index > -1 && index < values_.size())
			return values_[index];
		return 0;
	}
protected:
	QVector<const FieldValue*> values_;
};

