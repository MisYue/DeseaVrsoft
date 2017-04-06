#include "PowerAnalysisBaseData.h"
#include <MaterialLib/materiallib.h>

PowerAnalysisBaseData::PowerAnalysisBaseData(const WarheadModelWrap* model_wrap)
	: model_wrap_(model_wrap)
	, warhead_(model_wrap->get_structure())
{
	//Q_ASSERT(warhead_);
}


PowerAnalysisBaseData::~PowerAnalysisBaseData(void)
{
	if(warhead_)
		delete warhead_;
}
void PowerAnalysisBaseData::set_warhead_wrap(WarheadModelWrap* warhead_wrap) 
{
	model_wrap_ = warhead_wrap;
	warhead_ = model_wrap_->get_structure();
}

//获取基础数据
QString PowerAnalysisBaseData::GetData(const QString& key) const
{
	//当基础数据扩展频繁时，可以考虑使用脚本
	WarheadCharacterData character_data = warhead_->get_character_data();
	Bit_UnitSystem us = warhead_->get_cs().Get_UnitSystem();
	if(key == "WARHEAD_TOTAL_MASS")
		return QString::number(character_data.mass);
	else if(key == "WARHEAD_CHARGE_MASS")
		return QString::number(character_data.charge_mass);
	else if(key == "LENGTH_COEF")
		return QString::number(us.Get_LengthUnit());
	else if(key == "MASS_COEF")
		return QString::number(us.Get_MassUnit());
	else if(key == "TIME_COEF")
		return QString::number(us.Get_TimeUnit());
	else if(key == "CHARGE_ID")
		return warhead_->GetChargeId();
	else if(key == "CHARGE_DENSITY")
	{
		const ChargeMaterial* material = dynamic_cast<const ChargeMaterial*>(model_wrap_->get_charge_lib()->GetMaterial(warhead_->GetChargeId()));
		if(material)
			return QString::number(material->get_density(us));
		return QString();
	}
	else if(key == "CHARGE_EXPLOSION_VELOCITY")
	{
		const ChargeMaterial* material = dynamic_cast<const ChargeMaterial*>(model_wrap_->get_charge_lib()->GetMaterial(warhead_->GetChargeId()));
		if(material)
			return QString::number(material->get_velocity(us));
		return QString();
	}
	else if(key == "CHARGE_EXPLOSION_HEAT")
	{
		const ChargeMaterial* material = dynamic_cast<const ChargeMaterial*>(model_wrap_->get_charge_lib()->GetMaterial(warhead_->GetChargeId()));
		if(material)
			return QString::number(material->get_heat(us));
		return QString();
	}
	else if(key == "CHARGE_EXPLOSIN_PRESSURE")
	{
		const ChargeMaterial* material = dynamic_cast<const ChargeMaterial*>(model_wrap_->get_charge_lib()->GetMaterial(warhead_->GetChargeId()));
		if(material)
			return QString::number(material->get_pressure(us));
		return QString();
	}
	return QString();
}