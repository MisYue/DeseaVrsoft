/********************************************************************
created:	2016/10/15
 
file base:	BIT_DAMAGESIMULATION_API
file ext:	h
author:		Xuyuxin

purpose:	3维球(服务于目标等效模型)

*********************************************************************/

#include "Bit_3DModelSupport_Global.h"
#include "MathCalculationSupport/CoordinatesPosition.h"
//#include "MathCalculationSupport/AdvancedMath.h"

#ifndef BITSPHERE_H__
#define BITSPHERE_H__

class BIT3DMODELSUPPORT_API Bit_Sphere
{
public: 
	//构造函数
	Bit_Sphere ( void );
	//初始化构造函数
	Bit_Sphere ( CoordinatesPosition CP , double radius );
	//构造初始化函数根据圆的标准方程X^2+y^2+z^2+Dx+Ey+Fz+H=0的圆心点和共和半径
	Bit_Sphere ( double D , double E , double F , double H );

	//拷贝构造函数
	Bit_Sphere ( const Bit_Sphere &cSp );
	//运算符=重载
	Bit_Sphere &operator=( const Bit_Sphere &cSp );

	//设置初始化
	void Set_Initial_CPAndR( const CoordinatesPosition &CP , const	double &radius );

	//得到球心坐标
	inline CoordinatesPosition Get_CentrePoint( void )const;
	//得到球的半径
	inline double Get_Radius( void )const;
	//得到D

	//得到E

	//

private:
	//球心坐标
	CoordinatesPosition CP_;
	//球半径
	double radius_;
};
#endif