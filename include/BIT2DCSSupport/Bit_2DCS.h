/********************************************************************
created:	2016/08/24
 
file base:	BIT_DAMAGESIMULATION_API
file ext:	h
author:		Xuyuxin

purpose:	2维坐标系

*********************************************************************/

#include "Bit_2DCSSupport_Global.h"
#include "BITPointSupport/Bit_Point2D.h"
#include "BIT2DComputeSupport/Bit_2DCompute.h"

#ifndef BIT2DCS_H__
#define BIT2DCS_H__

class BIT2DCSSUPPORT_API Bit_2DCS
{
public:
	// 空构造函数
	Bit_2DCS(void);
	// 初始构造函数
	Bit_2DCS( Bit_Point2D OriginalPoint , int n, Bit_Point2D AixVector );
	// 拷贝构造函数
	Bit_2DCS( const Bit_2DCS &c2DC );
	//重载等号
	Bit_2DCS & operator = ( const Bit_2DCS & c2DC );
	//重载恒等于
	bool operator == ( const Bit_2DCS & c2DC ) const;
	//重载不等于
	bool operator != ( const Bit_2DCS & c2DC ) const;

	// 析构函数
	~Bit_2DCS(void);
	
	//设置初始参数
	void Set_Initial( const Bit_Point2D& OriginalPoint , const int& n , const Bit_Point2D& AixVector );
	//得到坐标原点
	inline Bit_Point2D Get_OriginalPoint( void ) const;
	//得到X轴向量
	inline  Bit_Point2D Get_XAixVector( void ) const;
	//得到Y轴向量
	inline  Bit_Point2D Get_YAixVector( void ) const;
private:
	// 坐标原点
	Bit_Point2D OriginalPoint_;
	// X轴向量
	Bit_Point2D X_AixVector_;
	// Y轴向量
	Bit_Point2D Y_AixVector_;
};

#endif

