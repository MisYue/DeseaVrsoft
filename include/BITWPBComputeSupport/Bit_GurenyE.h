//#pragma once
/********************************************************************
created:	2016/11/25
 
file base:	BITWPBCOMPUTESUPPORT_API
file ext:	h
author:		Xuyuxin

purpose:	计算格尼能

*********************************************************************/
#ifndef BITGURENYE_H__
#define BITGURENYE_H__
// 动态库导出
#include "Bit_WPBComputeSupport_Global.h"
// 
//#include "BITMaterialDataBase/Bit_ChargeData.h"
// 单位制
#include "BITUnitsSupport/Bit_UnitSystem.h"
#include "BITUnitsSupport/Bit_USTransform.h"
// csv表输入数据
//#include "BITFileExtend/Bit_CSVFile.h"

enum GEqutationType
{
	GEquation_1 ,			//公式一
	GEquation_2 				//公式二
};

class BITWPBCOMPUTESUPPORT_API Bit_GurenyE
{
public:
	Bit_GurenyE(void);
	~Bit_GurenyE(void);

	//*********公式说明*********
	string EquationExplain(const GEqutationType & Type)
	{
		switch( Type )
		{
		case GEquation_1:
			return "计算公式1：来自于终点效应学P78，需一个爆速参数，两个系数";
			break;
		case GEquation_2:
			return "计算公式2：来自于沈飞、王辉、袁建飞、田清政《炸药格尼系数的一种简易估算法》，需一个炸药装药密度参数，两个系数";
			break;
		default:
			exit(0);
			break;
		}
	}
	//设置参数
	//
	void SetIniParameters( const GEqutationType &Type, const double Parameter[] 
	, const Bit_UnitSystem ParaUs[], const double Cof[] ,const Bit_UnitSystem CofUs )
	{
		//设置系数
		for ( int i = 0 ; i < 10 ; i++ )
		{
			Coef_[i] = Cof[i];
		}
		Bit_USTransform *TheBit_USTransform = new Bit_USTransform;
		//比较系数与参数的单位后设置参数
		switch( Type )
		{
		case GEquation_1:
			Parameter_[0] = TheBit_USTransform->
				TransformValue( ParaUs[0] , CofUs , Parameter[0] , Velocity );
			IfUS_ = true;
			break;
		case GEquation_2:
			Bit_USTransform *TheBit_USTransform = new Bit_USTransform;
			Parameter_[0] = TheBit_USTransform->
				TransformValue( ParaUs[0] , CofUs , Parameter[0] , Density );
			Parameter_[1] = TheBit_USTransform->
				TransformValue( ParaUs[1] , CofUs , Parameter[1] , Velocity );
			IfUS_ = true;
			break;
		}

		delete TheBit_USTransform;
		IfDefine_ = true;
	}
	//计算
	void Compute( const GEqutationType & Type ); //公式

	//*********得到相关参数***********
	// 得到参数是否定义
	bool Get_IfDefine( void ) const;
	// 得到是否已计算
	bool Get_IfCompute( void ) const;
	// 得到单位制是否定义
	bool Get_IfUS( void ) const;
	// 得到格尼能
	double Get_GE( void ) const;
	// 得到参数
	double Get_Parameter( int ii ) const;
	// 得到系数
	double Get_Coef( int ii ) const;

private:
	double Parameter_[10];		//计算参数
	double Coef_[10];			//系数
	double GE_;					//格尼能
	Bit_UnitSystem US_;			//格尼能单位制
	bool IfUS_;
	bool IfDefine_;				//是否定义
	bool IfCompute_;			//是否计算

	///////////*******成熟算子************************
	// 计算格尼能公式1
	double GurenyEnergy_F1( void )const;
	// 计算格尼能公式2
	double GurenyEnergy_F2( void )const;
};
#endif
