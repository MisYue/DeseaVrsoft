//#pragma once
/********************************************************************
created:	2016/07/01
 
file base:	BIT_DAMAGESIMULATION_API
file ext:	h
author:		Xuyuxin

purpose:	弹体坐标系

*********************************************************************/

// 动态库导出
#include "Bit_3DCSSupport_Global.h"
//坐标系描述
#include "Bit_3DCS.h"
#include "Bit_3DCSWithExpAndUS.h"
#include "Bit_3DCSWithExplain.h"
#include "BITPointSupport/Bit_Point3D.h"

#ifndef BITPROJECTILECS_H__
#define BITPROJECTILECS_H__

class BIT3DCSSUPPORT_API Bit_3DProjectileCS
{
public:
	// 空函数
	Bit_3DProjectileCS(void);

	// 拷贝构造函数
	Bit_3DProjectileCS( const Bit_3DProjectileCS& cPCS);
	// 重载"="号函数
	Bit_3DProjectileCS& operator= (const Bit_3DProjectileCS& cPCS );
	// 重载"=="号
	bool operator == (const Bit_3DProjectileCS& cPCS )const;
	// 重载"!="号
	bool operator != (const Bit_3DProjectileCS& cPCS )const;
	~Bit_3DProjectileCS(void);
	//通过设置进行坐标系的初始化
	inline void Set_ProjectileCS( const Bit_3DCSWithExpAndUS& RCS );
	//单位制度转换
	// 三个单位均转换但是不输出
	inline void TransitionUS( const Bit_UnitSystem& NewUS );


private:
	//带描述的直角坐标系
	Bit_3DCSWithExpAndUS RCS_;
	//判断是否设置了单位系统
	bool IfUS_;
	//弹体坐标系内在大地坐标系内的三个角
	// 俯仰角(弧度)
	double PitchingAngle_;
	// 偏航角(弧度)
	double YawAngle_;
	// 滚转角(弧度)
	double RollAngle_;
};

#endif

