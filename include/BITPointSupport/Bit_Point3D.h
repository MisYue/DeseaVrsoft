/********************************************************************
created:	2015/11/03
 
file base:	BIT_DAMAGESIMULATION_API
file ext:	h
author:		Xuyuxin

purpose:	坐标定义及转换函数

*********************************************************************/

#ifndef BITPOINT3D_H__
#define BITPOINT3D_H__

#include "Bit_PointSupport_Global.h"

// 坐标点函数
//#include <iostream>
//#include <math.h>
//namespace BIT
//{
class BITPOINTSUPPORT_API Bit_Point3D
{
public:
	// 构造空的坐标
	Bit_Point3D(void);
	// 构造初始值坐标
	Bit_Point3D( double x, double y, double z );
	// 构造拷贝构造函数
	Bit_Point3D( const Bit_Point3D& cPositon);

	// 重载等号
	Bit_Point3D& operator= (const Bit_Point3D& cPositon );
	// 重载减号
	Bit_Point3D operator- (const Bit_Point3D& cPositon )const;
	// 重载加号
	Bit_Point3D operator+ (const Bit_Point3D& cPositon )const;
	//重载加等于
	Bit_Point3D & operator += ( const Bit_Point3D & cPoint );
	//重载减等于
	Bit_Point3D & operator -= ( const Bit_Point3D & cPoint );
	// 重载（点）乘号，每个数相乘
	Bit_Point3D operator* (const Bit_Point3D& cPositon )const;

	// 重载恒等判断
	bool operator == (const Bit_Point3D& cPositon )const;
	// 不等判断
	bool operator != (const Bit_Point3D& cPositon )const;

	~Bit_Point3D(void);

	//设置x值
	inline void Set_x(const double& xx );
	//设置y值
	inline void Set_y(const double& yy );
	//设置z值
	inline void Set_z(const double& zz );

	// 得到点中的x值
	inline double Get_x(void) const ;
	// 得到点中的y值
	inline double Get_y(void) const ;
	// 得到点中的z值
	inline double Get_z(void) const ;

	// 计算两点坐标间的距离
	inline double Distance(const Bit_Point3D& p2) const;

private:
	double x_;
	double y_;
	double z_;
};
//}

#endif