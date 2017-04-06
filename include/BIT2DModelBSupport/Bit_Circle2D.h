//#pragma once
/********************************************************************
created:	2016/08/20
 
file base:	BIT_DAMAGESIMULATION_API
file ext:	h
author:		Xuyuxin

purpose:	2维圆数据结构

*********************************************************************/

#include "Bit_2DModelBSupport_Global.h"
#include "BITPointSupport/Bit_Point2D.h"

#ifndef BITCIRCLE2D_H__
#define BITCIRCLE2D_H__

class BIT2DMODELBSUPPORT_API Bit_Circle2D
{
public:
	// 空函数
	Bit_Circle2D(void);
	// 构造初始化函数
	Bit_Circle2D( Bit_Point2D CentreP , double Radius );
	// 构造初始化函数根据圆的标准方程X^2+y^2+Dx+Ey+F=0的圆心点和共和半径
	Bit_Circle2D( double D , double E , double F );

	//拷贝构造函数
	Bit_Circle2D( const Bit_Circle2D &cC2D );
	//重载等号
	Bit_Circle2D & operator = ( const Bit_Circle2D & cC2D );
	//重载等于
	bool operator == ( const Bit_Circle2D & cC2D ) const;
	//重载不等于
	bool operator != ( const Bit_Circle2D & cC2D ) const;

	~Bit_Circle2D(void);

	// 初始化设置
	void Set_Initial( const Bit_Point2D& CentreP , const double& Radius );
	// 得到是否定义
	inline bool Get_IfDefinition( void ) const;
	// 得到圆心点
	inline Bit_Point2D Get_CentreP( void ) const;
	// 得到直径
	inline double Get_Radius( void ) const;
	// 得到标准化方程的D
	inline double Get_StandardD( void ) const;
	// 得到标准化方程的E
	inline double Get_StandardE( void ) const;
	// 得到标准化方程的F
	inline double Get_StandardF( void ) const;
	// 判断点是否在圆上
	inline bool JudgePointIfInCircle( const Bit_Point2D & P )const;

private:
	// 圆心点
	Bit_Point2D CentreP_;
	// 半径
	double Radius_;
	// 圆是否定义
	bool IfDefinition_;
};
#endif
