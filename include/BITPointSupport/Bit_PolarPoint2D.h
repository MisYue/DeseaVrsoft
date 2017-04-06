//#pragma once
/********************************************************************
created:	2016/08/20
 
file base:	BIT_DAMAGESIMULATION_API
file ext:	h
author:		wangxiao

purpose:	2维极坐标点数据结构

*********************************************************************/

#include "Bit_PointSupport_Global.h"

#ifndef BITPLOLARPOINT2D_H__
#define BITPLOLARPOINT2D_H__


class BITPOINTSUPPORT_API Bit_PolarPoint2D
{
public:
	// 空
	Bit_PolarPoint2D(void);
	// 构造初始函数
	Bit_PolarPoint2D( double Radius, double AngleR );
	// 拷贝构造函数
	Bit_PolarPoint2D( const Bit_PolarPoint2D& cPP2D);

	// 析构函数
	~Bit_PolarPoint2D(void);

	// 重载等号
	Bit_PolarPoint2D& operator= (const Bit_PolarPoint2D& cPP2D );
	// 重载减号
	Bit_PolarPoint2D operator- (const Bit_PolarPoint2D& cPP2D )const;
	// 重载加号
	Bit_PolarPoint2D operator+ (const Bit_PolarPoint2D& cPP2D )const;
	// 重载恒等判断
	bool operator == (const Bit_PolarPoint2D& cPP2D )const;
	// 重载不等判断
	bool operator != (const Bit_PolarPoint2D& cPP2D )const;

	//设置所有参数
	inline void Set_Initial( const double& Radius , const double& AngleR );
	//设置径向距离值
	inline void Set_Radius(const double& Radius );
	//设置角度(弧度)值
	inline void Set_AngleR(const double& AngleR );

	// 得到点中的径向距离值
	inline double Get_Radius(void) const ;
	// 得到点中的角度(弧度)值
	inline double Get_AngleR(void) const ;

private:
	double Radius_;
	double AngleR_;

};
#endif
