/********************************************************************
created:	2016/08/20
 
file base:	BIT_DAMAGESIMULATION_API
file ext:	h
author:		Xuyuxin

purpose:	2维圆弧数据结构

*********************************************************************/

#include "Bit_2DModelBSupport_Global.h"
#include "BITPointSupport/Bit_Point2D.h"
#include "BIT2DComputeSupport/Bit_2DCompute.h"

#ifndef BITARC2D_H__
#define BITARC2D_H__

class BIT2DMODELBSUPPORT_API Bit_Arc2D
{
public:
	Bit_Arc2D(void);
	// 构造初始化函数
	Bit_Arc2D( Bit_Point2D CentreP , Bit_Point2D FristP , double Radian );

	//拷贝构造函数
	Bit_Arc2D( const Bit_Arc2D &cA2D );
	//重载等号
	Bit_Arc2D & operator = ( const Bit_Arc2D & cA2D );
	//重载恒等于
	bool operator == ( const Bit_Arc2D & cA2D ) const;
	//重载不等于
	bool operator != ( const Bit_Arc2D & cA2D ) const;
	//析构函数
	~Bit_Arc2D(void);

	// 初始化设置
	void Set_Initial( const Bit_Point2D& CentreP ,const Bit_Point2D &FristP ,const double &Radian );
	// 得到是否定义
	inline bool Get_IfDefinition( void ) const;
	// 得到圆心点
	inline Bit_Point2D Get_CentreP( void ) const;
	// 得到弧度
	inline double Get_Radian( void ) const;
	// 得到半径
	inline double Get_Radius( void ) const;
	// 得到第一点
	inline Bit_Point2D Get_FirstP( void ) const;
	// 得到第二点
	inline Bit_Point2D Get_SecondP( void ) const;
	// 判断点是否在圆弧上
	inline bool JudgePointIfInArc( const Bit_Point2D & P )const;

private:
	// 圆心点
	Bit_Point2D CentreP_;
	// 半径
	double Radius_;
	// 第一个点
	Bit_Point2D FristP_;
	// 弧度(从第一个点转过，逆时针为正,顺时针为负，0~2Pi弧度)
	double Radian_;
	// 圆弧是否定义
	bool IfDefinition_;
};
#endif

