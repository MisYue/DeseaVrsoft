//#pragma once
/********************************************************************
created:	2016/12/20
 
file base:	BIT_DAMAGESIMULATION_API
file ext:	h
author:		Xuyuxin

purpose:	单位系转换计算函数

*********************************************************************/

#ifndef BITUSTRANSFORM_H__
#define BITUSTRANSFORM_H__

#include "Bit_UnitSystem.h"

enum SUnitType
{
	Length,			//长度
	Mass,			//质量
	Time,			//时间
	StrainRate,		//应变率
	Density,		//密度
	Force,			//力
	Pressure,		//压强
	Energy,			//能量
	Velocity,		//速度
	Area,			//面积
	Volum,			//体积
	ContrastDis,	//对比距离
	VRC,			//速度衰减系数
};


class BITUNITSSUPPORT_API Bit_USTransform
{
public:
	Bit_USTransform(void);
	~Bit_USTransform(void);

	//**************单个值的转换*****************
	double TransformValue(const Bit_UnitSystem& Old_us
		, const Bit_UnitSystem& New_us, const double& Value
		, const SUnitType& Type)const;
	
	//**************坐标值的转换*****************
	// 3D坐标值转换
	inline Bit_Point3D TransformPoint3D( const Bit_UnitSystem& Old_us 
		, const Bit_UnitSystem& New_us , const Bit_Point3D &P )const;
	// 2D坐标值转换
	inline Bit_Point2D TransformPoint2D( const Bit_UnitSystem& Old_us 
		, const Bit_UnitSystem& New_us , const Bit_Point2D &P )const;
};
#endif
