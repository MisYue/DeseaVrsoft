//#pragma once

/********************************************************************
created:	2016/10/07
 
file base:	BIT_DAMAGESIMULATION_API
file ext:	h
author:		Xuyuxin

purpose:	3维圆柱体(服务于目标等效模型)

*********************************************************************/
#include "MathCalculationSupport/CoordinatesPosition.h"
#include "Bit_3DModelSupport_Global.h"

#ifndef BITCYLINDER_H__
#define BITCYLINDER_H__

class BIT3DMODELSUPPORT_API Bit_Cylinder
{
public:
	// 空函数
	Bit_Cylinder(void);
	// 构造函数
	Bit_Cylinder( CoordinatesPosition CP , double radius , double High 
		, CoordinatesPosition CAxisV );
	// 拷贝构造函数
	Bit_Cylinder( const Bit_Cylinder &cCl );
	//重载等号
	Bit_Cylinder & operator = ( const Bit_Cylinder &cCl );
	//重载恒等于
	bool operator == ( const Bit_Cylinder &cCl ) const;
	//重载不等于
	bool operator != ( const Bit_Cylinder &cCl ) const;

	~Bit_Cylinder(void);

	// 设置初始化
	void Set_Initial( const CoordinatesPosition& CP , const double& radius 
		, const double& High, const CoordinatesPosition& CV );

	//得到中心点
	inline CoordinatesPosition Get_CP( void )const;
	//得到半径
	inline double Get_radius( void )const;
	//得到高度
	inline double Get_High( void )const;
	//得到轴的矢量方向
	inline CoordinatesPosition Get_CAxisV( void )const;

private:
	// 中心点坐标
	CoordinatesPosition CP_;
	//半径
	double radius_;
	//高度
	double High_;
	//轴的矢量方向
	CoordinatesPosition CAxisV_;
};
#endif
