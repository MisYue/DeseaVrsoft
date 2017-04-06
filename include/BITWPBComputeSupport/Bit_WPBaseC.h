/********************************************************************
created:	2016/2/2
 
file base:	BIT_DAMAGESIMULATION_API
file ext:	h
author:		Xuyuxin

purpose:	进行基础计算

*********************************************************************/

#ifndef BITWPBASEC_H__
#define BITWPBASEC_H__
// 动态库导出
#include "Bit_WPBComputeSupport_Global.h"
// 战斗部基础数据
#include "BITWarheadData/Bit_WarheadBaseData.h"

class BITWPBCOMPUTESUPPORT_API Bit_WPBaseC
{
public:
	// 空构造函数
	Bit_WPBaseC(void);

	~Bit_WPBaseC(void);

	//***********************非战斗部、装药数据结构参量计算****************************
	//返回：战斗部整体装药与壳体质量比
	double ComputeMassRatioForChargeAndShell( const double& WholeMass
		, const double& ChargesMass, const double& ShellMass)const;
	//计算战斗部圆柱段装药和壳体质量比
	inline double ComputeMassRatioForChargeAndShellInClinder( const double& ChargeMassInClinder
		, const double &ShellMassInClinder )const;
	//计算战斗部装填系数
	inline double ComputeFillCoefficient( const double& WarWholeMass, const double& ChargeWholeMass )const;
	//
	//***********************战斗部、装药数据结构参量计算****************************
	// 战斗部整体装药与壳体质量比
	double ComputeMassRatioForChargeAndShellOnWarD( const Bit_WarheadBaseData &WarheadD)const;
	// 计算战斗部圆柱段装药和壳体质量比
	double ComputeMassRatioForChargeAndShellInClinderOnWarD( const Bit_WarheadBaseData &WarheadD )const;
	// 计算战斗部装填系数
	double ComputeFillCoefficientOnWarD( const Bit_WarheadBaseData &WarheadD )const;
};

#endif