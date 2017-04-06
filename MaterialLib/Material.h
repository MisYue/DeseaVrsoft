#pragma once
#include "materiallib_global.h"
#include <BITUnitsSupport/Bit_UnitSystem.h>
#ifdef pi
#undef pi
#endif
#include <QtCore>

//材料类型
enum MaterialType
{
	kMetal,	//金属
	kExplosive, //炸药
};

class MATERIALLIB_EXPORT Material
{
public:
	Material() : density_(0)  {}
	virtual ~Material() {}

	void set_id(const QString& id) { id_ = id; }
	QString get_id() const { return id_; }

	void set_name(const QString& name) { name_ = name; }
	QString get_name() const { return name_; }

	void set_us(const Bit_UnitSystem& us) { us_ = us; }
	Bit_UnitSystem get_us() const { return us_; }

	void set_density(double density) { density_ = density; }
	double get_density() const { return density_; }
	double get_density(const Bit_UnitSystem& us) const;

	void SetPropertyValues(const QStringList& values) { property_values_ = values; }
	QStringList GetPropertyValues() const { return property_values_; }


protected:
	QString id_;
	QString name_;
	Bit_UnitSystem us_;
	double density_;

	QStringList property_values_;	//属性值列表
};

