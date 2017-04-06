#include <WarheadModelData/WarheadModelWrap.h>
#include <BasicTool/expandqtcore.h>
#include <BasicTool/EnumMgr.h>
#include <MaterialLib/ChargeLib.h>
#include <MaterialLib/MetalLib.h>

class StaticIniter
{
public:
	StaticIniter()
	{
		EnumMgr& enum_mgr = EnumMgr::instance();
		enum_mgr.AddEnum<WarheadModelWrap::UnitLength>(WarheadModelWrap::kMm, ExpandQtCore::fromGBK("mm"));
		enum_mgr.AddEnum<WarheadModelWrap::UnitLength>(WarheadModelWrap::kCm, ExpandQtCore::fromGBK("cm"));
		enum_mgr.AddEnum<WarheadModelWrap::UnitLength>(WarheadModelWrap::kM, ExpandQtCore::fromGBK("m"));
		enum_mgr.AddEnum<WarheadModelWrap::UnitLength>(WarheadModelWrap::kKm, ExpandQtCore::fromGBK("km"));
		enum_mgr.AddEnum<WarheadModelWrap::UnitMass>(WarheadModelWrap::kG, ExpandQtCore::fromGBK("g"));
		enum_mgr.AddEnum<WarheadModelWrap::UnitMass>(WarheadModelWrap::kKg, ExpandQtCore::fromGBK("kg"));

	}
};


WarheadModelWrap::WarheadModelWrap()
	: structure_(new WarheadModel)
	, metal_lib_(new MetalLib)
	, charge_lib_(new ChargeLib)
{
}


WarheadModelWrap::~WarheadModelWrap(void)
{
	delete structure_;
	delete metal_lib_;
	delete charge_lib_;
}

// 获取系统建议的长度精度，返回小数位数
int WarheadModelWrap::GetLengthPrecisionHint() const
{
	Q_ASSERT(structure_);
	Bit_UnitSystem us = structure_->get_cs().Get_UnitSystem();
	int length_unit = us.Get_LengthUnit();
	int result = 0;
	switch(length_unit)
	{
	case 1: result = 0; break;
	case 2: result = 1; break;
	case 3: result = 2; break;
	case 4: result = 5; break;
	default:
		Q_ASSERT(0);
	}
	return result + 3;	//mm 0.001
}

// 获取系统建议的质量精度，返回小数位数
int WarheadModelWrap::GetMassPrecisionHint() const
{
	Q_ASSERT(structure_);
	Bit_UnitSystem us = structure_->get_cs().Get_UnitSystem();
	int mass_unit = us.Get_MassUnit();
	int result = 0;
	switch(mass_unit)
	{
	case 1: result = 0; break;
	case 2: result = 3; break;
	default:
		Q_ASSERT(0);
	}
	return result + 3;	//g 0.001
}

// 获取长度单位
QString WarheadModelWrap::GetLengthUnit() const
{
	Q_ASSERT(structure_);
	Bit_UnitSystem us = structure_->get_cs().Get_UnitSystem();
	int length_unit = us.Get_LengthUnit();
	return EnumMgr::instance().GetEnumName<WarheadModelWrap::UnitLength>(static_cast<WarheadModelWrap::UnitLength>(length_unit));
}

// 获取质量单位
QString WarheadModelWrap::GetMassUnit() const
{
	Q_ASSERT(structure_);
	Bit_UnitSystem us = structure_->get_cs().Get_UnitSystem();
	int mass_unit = us.Get_MassUnit();
	return EnumMgr::instance().GetEnumName<WarheadModelWrap::UnitLength>(static_cast<WarheadModelWrap::UnitLength>(mass_unit));
}