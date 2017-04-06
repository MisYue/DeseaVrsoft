//#pragma once
/********************************************************************
created:	2016/10/28
 
file base:	BIT_DAMAGESIMULATION_API
file ext:	h
author:		Xuyuxin

purpose:	3维半球球(服务于目标等效模型)

*********************************************************************/
#include "Bit_3DModelSupport_Global.h"
#include "MathCalculationSupport/CoordinatesPosition.h"

#ifndef BITSELFSPHERE_H__
#define BITSELFSPHERE_H__

class BIT3DMODELSUPPORT_API Bit_SelfSphere
{
public:
	// 空函数
	Bit_SelfSphere(void);
	// 初始构造函数
	Bit_SelfSphere( CoordinatesPosition CP , double radius , CoordinatesPosition CV );
	// 拷贝构造函数
	Bit_SelfSphere( const Bit_SelfSphere &cSS );
	//重载等号
	Bit_SelfSphere & operator = ( const Bit_SelfSphere & cSS );
	//重载恒等于
	bool operator == ( const Bit_SelfSphere & cSS ) const;
	//重载不等于
	bool operator != ( const Bit_SelfSphere & cSS ) const;
	//析构函数
	~Bit_SelfSphere(void);

	// 设置初始化
	void Set_Initial( const CoordinatesPosition& CP , const double& radius 
		, const CoordinatesPosition& CV  );
	//得到中心点
	inline CoordinatesPosition Get_CP( void )const;
	//得到球半径
	inline double Get_radius( void )const;
	//得到轴的矢量方向(指向球弧)
	inline CoordinatesPosition Get_CV( void )const;

private:
	//球心坐标
	CoordinatesPosition CP_;
	//球半径
	double radius_;
	//轴的矢量方向(指向球弧)
	CoordinatesPosition CAxisV_;
};
#endif
