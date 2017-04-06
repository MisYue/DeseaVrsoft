//
/********************************************************************
created:	2016/03/19
 
file base:	BIT_DAMAGESIMULATION_API
file ext:	h
author:		Xuyuxin

purpose:	柱面坐标系的定义

*********************************************************************/

#ifndef BITCYLINDERCOSYSTEM_H__
#define BITCYLINDERCOSYSTEM_H__


// 动态库导出
#include "Bit_3DCSSupport_Global.h"
// 直角坐标坐标系类
#include "Bit_3DCS.h"

#include "BITPointSupport/Bit_Point3D.h"

#include "BIT3DComputeSupport/Bit_3DCompute.h"

class BIT3DCSSUPPORT_API Bit_3DCylinderCS
{
public:
	// 空构造函数
	Bit_3DCylinderCS(void);
	// 初始构造函数
	Bit_3DCylinderCS( Bit_Point3D OriginalPoint 
		, Bit_Point3D Polar_Vector , Bit_Point3D Z_Vector );

	// 拷贝构造函数
	Bit_3DCylinderCS( const Bit_3DCylinderCS &cCCS );
	// 重载"="等号
	Bit_3DCylinderCS& operator= (const Bit_3DCylinderCS& cCCS );
	// 重载"=="恒等判断
	bool operator == (const Bit_3DCylinderCS& cCCS )const;

	~Bit_3DCylinderCS(void);

	// 初始化设置
	void Set_Initial( const Bit_Point3D& OriginalPoint 
		, const Bit_Point3D& Polar_Vector ,const Bit_Point3D& Z_Vector);
	
	//空间坐标系转换到柱面坐标系
	void TransformFromCSToCCS( const int &XorY , const Bit_3DCS &CP_CS );
	//空间坐标系(指针)转换到柱面坐标系
	void TransformFromCS_PToCCS( const int &XorY , const Bit_3DCS *CP_CS );
	
	// 得到原点
	inline Bit_Point3D Get_OriginalPoint(void) const ;
	// 得到极轴向量
	inline Bit_Point3D Get_PolarAixVector(void) const ;
	// 得到Z轴向量
	inline Bit_Point3D Get_ZAixVector(void) const;
	

private:
	// 坐标原点
	Bit_Point3D OriginalPoint_;
	// 极轴向量
	Bit_Point3D Polar_AixVector_;
	// Z轴向量
	Bit_Point3D Z_AixVector_;
};

#endif

