/********************************************************************
created:	2016/08/20
 
file base:	BIT_DAMAGESIMULATION_API
file ext:	h
author:		wangxiao

purpose:	2维点数据结构

*********************************************************************/
#include "Bit_PointSupport_Global.h"

#ifndef BITPOINT2D_H__
#define BITPOINT2D_H__

class BITPOINTSUPPORT_API Bit_Point2D
{
public: 
	//默认空构造函数
	Bit_Point2D();
	//带参数的构造函数
	Bit_Point2D( double xx , double yy );
	//拷贝构造函数
	Bit_Point2D( const Bit_Point2D &cPoint );

	//重载等号
	Bit_Point2D & operator = ( const Bit_Point2D & cPoint );
	//重载加号
	Bit_Point2D operator + ( const Bit_Point2D & cPoint ) const;
	//重载减号
	Bit_Point2D operator - ( const Bit_Point2D & cPoint ) const;
	//重载加等于
	Bit_Point2D & operator += ( const Bit_Point2D & cPoint );
	//重载减等于
	Bit_Point2D & operator -= ( const Bit_Point2D & cPoint );
	//重载恒等于
	bool operator == ( const Bit_Point2D & cPoint ) const;
	//重载不等于
	bool operator != ( const Bit_Point2D & cPoint ) const;

	//析构函数
	~Bit_Point2D();

	//设置单个坐标
	void Set_x( double xx );
	void Set_y( double yy );

	//获取单个坐标
	double Get_x( void ) const;
	double Get_y( void ) const;

private:
	double x_;//x坐标
	double y_;//y坐标
};
#endif