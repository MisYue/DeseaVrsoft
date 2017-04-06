#pragma once
#include "basictool_global.h"
#include <QtCore>

class BASICTOOL_EXPORT EnumFeature
{
public:
	EnumFeature(void) {}
	~EnumFeature(void) {}
	template <class T>
	T GetEnumValue(const QString& name)
	{
		return static_cast<T>(value_2_name_.key(name, 0));
	}
	template <class T>
	QString GetEnumName(const T& value)
	{
		return value_2_name_.value(value);
	}
	QStringList GetNames() const { return value_2_name_.values(); }
protected:
	QMap<int, QString> value_2_name_;
	template <class T>
	void AddEnum(const T& value, const QString& name)
	{
		value_2_name_.insert(value, name);
	}
};

