//#pragma once
/********************************************************************
created:	2016/12/9
 
file base:	BITWPBCOMPUTESUPPORT_API
file ext:	h
author:		Xuyuxin

purpose:	计算破片飞散角及飞散范围角（圆柱形战斗部）

*********************************************************************/
#ifndef BITSFRAGFLYANGLE_H__
#define BITSFRAGFLYANGLE_H__
// 动态库导出
#include "Bit_WPBComputeSupport_Global.h"
// 单位制
#include "BITUnitsSupport\Bit_UnitSystem.h"
#include "BITUnitsSupport\Bit_USTransform.h"
// 2D运算
#include "BIT2DComputeSupport\Bit_2DCompute.h"
// 2D点
#include "BITPointSupport\Bit_Point2D.h"

enum FVAEqutationType
{
	Taylor_Cy ,			//（圆柱壳体）泰勒公式
	Shapiro_Cy,			//（圆柱壳体）夏皮罗公式
	Shapiro_AS,			//（任意形状）夏皮罗公式
};

class BITWPBCOMPUTESUPPORT_API Bit_SFragFlyAngle
{
public:
	Bit_SFragFlyAngle(void);

	~Bit_SFragFlyAngle(void);

	//*********设置计算参数*********
	//基于坐标设置
	void SetIniParameters_P( const double & FV , const Bit_UnitSystem & FVU ,
		const double & EDV , const Bit_UnitSystem & EDVU ,
		const Bit_Point2D &FragP, const Bit_Point2D & ExploPoint ,const double & FNWAA )
	{
		//设置破片飞行初速
		FVelocity_ = FV;

		//比较破片初速与炸药爆速的单位后设置炸药爆速
		if ( FVU == EDVU )
		{
			EDVelocity_ = EDV;
			US_ = FVU;
		}
		else
		{
			Bit_USTransform *TheBit_USTransform = new Bit_USTransform;
			EDVelocity_ = TheBit_USTransform->TransformValue( EDVU , FVU , EDV , Velocity);
			delete TheBit_USTransform;
			US_ = FVU;
		}
		//设置破片及起爆点坐标
		FragP_ = FragP;
		ExploPoint_ = ExploPoint;
		//计算破片与炸点连线与弹轴正方向的夹角
		Bit_2DCompute *TheBit_2DCompute = new Bit_2DCompute;
		Bit_Point2D EFVector = FragP_ - ExploPoint_;//起爆点-破片位置连线向量
		FEWAA_ = TheBit_2DCompute->ComputeAnglePV_Xaxis( EFVector );
		delete TheBit_2DCompute;
		//设置破片法线与弹轴正方向的夹角
		FNWAA_ = FNWAA;
		IfDefine_ = true;
	}
	//基于角度设置
	void SetIniParameters_A( const double & FV , const Bit_UnitSystem & FVU ,
		const double & EDV , const Bit_UnitSystem & EDVU ,
		const double & FEWAA , const double & FNWAA )
	{
		//设置破片飞行初速
		FVelocity_ = FV;

		//比较破片初速与炸药爆速的单位后设置炸药爆速
		Bit_USTransform *TheBit_USTransform = new Bit_USTransform;
		EDVelocity_ = TheBit_USTransform->TransformValue( EDVU , FVU , EDV , Velocity);
		delete TheBit_USTransform;
		US_ = FVU;
		//设置破片与炸点连线与弹轴正方向的夹角
		FEWAA_ = FEWAA;
		//设置破片法线与弹轴正方向的夹角
		FNWAA_ = FNWAA;
		IfDefine_ = true;
	}


	//*********计算单个破片飞散角*****************
	void ComputeSFFlyA( const FVAEqutationType & ET );

	//*********得到相关参数***********
	// 得到参数是否定义
	bool Get_IfDefine( void ) const;
	// 得到破片初速
	double Get_FVelocity( void ) const;
	// 得到炸药爆速
	double Get_EDVelocity( void ) const;
	// 得到单位制
	Bit_UnitSystem Get_US( void ) const;
	// 得到破片位置坐标
	Bit_Point2D Get_FragP( void ) const;
	// 得到起爆点坐标
	Bit_Point2D Get_ExploPoint( void ) const;
	// 得到破片与炸点连线与弹轴正方向的夹角
	double Get_FEWAA( void ) const;
	// 得到破片法线与弹轴正方向的夹角
	double Get_FNWAA( void ) const;
	// 得到是否已计算
	bool Get_IfCompute( void ) const;
	// 得到单个破片飞散角
	double Get_SFFA( void ) const;

private:
	double FVelocity_;			//破片初速
	double EDVelocity_;			//炸药爆速
	Bit_UnitSystem US_;			//单位制
	Bit_Point2D FragP_;			//破片位置
	Bit_Point2D ExploPoint_;	//起爆点坐标
	double FEWAA_;				//破片与炸点连线与弹轴正方向的夹角
	double FNWAA_;				//破片法线与弹轴正方向的夹角;
	bool IfDefine_;				//是否定义

	double SFFA_;				//单个破片飞散角
	bool IfCompute_;			//是否计算

	//公式1，泰勒公式(只适应于圆柱)
	double Function_1( void )const;
	//公式2，适用于圆柱形壳体的夏皮罗公式
	double Function_2( void )const;
	//公式3，普适的泰勒公式
	double Function_3( void )const;
};
#endif
