//#pragma once

/********************************************************************
created:	2016/12/22
 
file base:	BITWPBCOMPUTESUPPORT_API
file ext:	h
author:		Xuyuxin

purpose:	计算单个破片速度

*********************************************************************/

#ifndef BITSFRAGVELOCITYC_H__
#define BITSFRAGVELOCITYC_H__
// 动态库导出
#include "Bit_WPBComputeSupport_Global.h"

// 单位制
#include "BITUnitsSupport/Bit_UnitSystem.h"
#include "BITUnitsSupport/Bit_USTransform.h"

enum FVEqutationType
{
	FVEquation_1 ,			//公式一
	FVEquation_2 				//公式二
};

class BITWPBCOMPUTESUPPORT_API Bit_SFragVelocityC
{
public:
	Bit_SFragVelocityC(void);
	~Bit_SFragVelocityC(void);

	//*********公式说明*********
	string EquationExplain(const FVEqutationType & Type)
	{
		switch( Type )
		{
		case FVEquation_1:
			return "计算公式1：来自于终点效应学P78，需两个参数：格尼能，装填比；一个系数";
			break;
		case FVEquation_2:
			return "计算公式2：来自于防空导弹引战配合效率与战斗部设计P274，需五个参数：微元到基准面距离，装药直径，装药长度，格尼能，微元处装填比；五个系数";
			break;
		default:
			exit(0);
			break;
		}
	}

	//设置参数
	void SetIniParameters( const FVEqutationType &Type, const double Parameter[] 
	, const Bit_UnitSystem ParaUs[], const double Coef[] ,const Bit_UnitSystem CoefUs )
	{
		//设置系数
		for ( int i = 0 ; i < 10 ; i++ )
		{
			Coef_[i] = Coef[i];
		}
		Bit_USTransform *TheBit_USTransform = new Bit_USTransform;
		//比较系数与参数的单位后设置参数
		switch( Type )
		{
		case FVEquation_1:
			Parameter_[0] = TheBit_USTransform->
				TransformValue( ParaUs[0] , CoefUs , Parameter[0] , Velocity );
			Parameter_[1] = Parameter[1] ;
			IfUS_ = true;
			break;
		case FVEquation_2:
			Bit_USTransform *TheBit_USTransform = new Bit_USTransform;
			Parameter_[0] = TheBit_USTransform->
				TransformValue( ParaUs[0] , CoefUs , Parameter[0] , Length );
			Parameter_[1] = TheBit_USTransform->
				TransformValue( ParaUs[1] , CoefUs , Parameter[1] , Length );
			Parameter_[2] = TheBit_USTransform->
				TransformValue( ParaUs[2] , CoefUs , Parameter[2] , Length );
			Parameter_[4] = Parameter[4] ;
			IfUS_ = true;
			break;
		}
		delete TheBit_USTransform;
		IfDefine_ = true;
	}

	//计算
	void Compute( const FVEqutationType & Type ); //公式

	//*********得到相关参数***********
	// 得到参数是否定义
	bool Get_IfDefine( void ) const;
	// 得到是否已计算
	bool Get_IfCompute( void ) const;
	// 得到单位制是否定义
	bool Get_IfUS( void ) const;
	// 得到破片速度
	double Get_FV( void ) const;
	// 得到参数
	double Get_Parameter( int ii ) const;
	// 得到系数
	double Get_Coef( int ii ) const;

private:
	double Parameter_[10];		//计算参数
	double Coef_[10];			//系数
	double FV_;					//破片速度
	Bit_UnitSystem US_;			//破片速度单位制
	bool IfUS_;
	bool IfDefine_;				//是否定义
	bool IfCompute_;			//是否计算

	///////////*******成熟算子************************
	// 计算格尼能公式1
	double FragmentVelocity_F1( void )const;
	// 计算格尼能公式2
	double FragmentVelocity_F2( void )const;
};
#endif
