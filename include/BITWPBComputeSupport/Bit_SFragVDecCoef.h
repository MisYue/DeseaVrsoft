/********************************************************************
created:	2017/1/9
 
file base:	BITWPBCOMPUTESUPPORT_API
file ext:	h
author:		Xuyuxin

purpose:	计算破片速度衰减系数

*********************************************************************/
#ifndef BITBALLISTICLIM_H__
#define BITBALLISTICLIM_H__
// 动态库导出
#include "Bit_WPBComputeSupport_Global.h"
// 单位制
#include "BITUnitsSupport/Bit_UnitSystem.h"
#include "BITUnitsSupport/Bit_USTransform.h"

enum FVDCEqutationType
{
	FVDCEquation_1 			//公式一
};

class BITWPBCOMPUTESUPPORT_API Bit_SFragVDecCoef
{
public:
	Bit_SFragVDecCoef(void);
	~Bit_SFragVDecCoef(void);

	//*********公式说明*********
	string EquationExplain(const FVDCEqutationType & Type)
	{
		switch( Type )
		{
		case FVDCEquation_1:
			return "计算公式1：来自于终点效应学P88，需四个参数：破片气动阻力系数、空气密度、破片形状系数、破片质量；一个系数";
			break;
		default:
			exit(0);
			break;
		}
	}

	//设置参数
	void SetIniParameters( const FVDCEqutationType &Type, const double Parameter[] 
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
		case FVDCEquation_1:
			Parameter_[0] = Parameter[0];
			Parameter_[1] = TheBit_USTransform->
				TransformValue( ParaUs[1] , CofUs , Parameter[1] , Density );
			Parameter_[2] = Parameter[2];
			Parameter_[3] = TheBit_USTransform->
				TransformValue( ParaUs[3] , CofUs , Parameter[3] , Mass );
			IfUS_ = true;
			break;
		}

		delete TheBit_USTransform;
		IfDefine_ = true;
	}
	//计算
	void Compute( const FVDCEqutationType & Type ); //公式

	//*********得到相关参数***********
	// 得到参数是否定义
	bool Get_IfDefine( void ) const;
	// 得到是否已计算
	bool Get_IfCompute( void ) const;
	// 得到单位制是否定义
	bool Get_IfUS( void ) const;
	// 得到弹道极限
	double Get_BL( void ) const;
	// 得到参数
	double Get_Parameter( int ii ) const;
	// 得到系数
	double Get_Coef( int ii ) const;

private:
	double Parameter_[10];		//计算参数
	double Coef_[10];			//系数
	double VDC_;					//速度衰减系数
	Bit_UnitSystem US_;			//单位制
	bool IfUS_;
	bool IfDefine_;				//是否定义
	bool IfCompute_;			//是否计算

	///////////*******成熟算子************************
	// 计算弹道极限公式1
	double SFragVDecCoef_F1( void )const;
};
#endif

