#pragma once
#include "warhead_model.h"

class MaterialLib;
class WARHEADMODELDATA_EXPORT WarheadModelWrap
{
public:
	enum UnitLength
	{
		kMm = 1,
		kCm = 2,
		kM = 3,
		kKm = 4,
	};
	enum UnitMass
	{
		kG = 1,
		kKg = 2,
	};

	WarheadModelWrap();
	virtual ~WarheadModelWrap(void);
	// 获取结构
	WarheadModel* get_structure(void)
	{
		return structure_;
	}
	const WarheadModel* get_structure(void) const
	{
		return structure_;
	}

	// 获取金属库
	MaterialLib* get_metal_lib(void)
	{
		return metal_lib_;
	}
	const MaterialLib* get_metal_lib(void) const
	{
		return metal_lib_;
	}

	// 获取装药库
	MaterialLib* get_charge_lib(void)
	{
		return charge_lib_;
	}
	const MaterialLib* get_charge_lib(void) const
	{
		return charge_lib_;
	}

	// 获取系统建议的长度精度，返回小数位数
	int GetLengthPrecisionHint() const;

	// 获取系统建议的质量精度，返回小数位数
	int GetMassPrecisionHint() const;
	
	// 获取长度单位
	QString GetLengthUnit() const;

	// 获取质量单位
	QString GetMassUnit() const;

protected:
	// 结构
	WarheadModel* structure_;
	// 金属库
	MaterialLib* metal_lib_;
	// 装药库
	MaterialLib* charge_lib_;
};

