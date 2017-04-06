/********************************************************************
created:	2015/11/03
 
file base:	BIT_DAMAGESIMULATION_API
file ext:	h
author:		Xuyuxin

purpose:	坐标系定义

*********************************************************************/

#ifndef BIT3DCS_H__
#define BIT3DCS_H__

#include "Bit_3DCSSupport_Global.h"
// 三维点类
#include "BITPointSupport/Bit_Point3D.h"
// 空间几何计算类
#include "BIT3DComputeSupport/Bit_3DCompute.h"
//数学计算类
#include "BITMathSupport/Bit_AdvMathCompute.h"

class BIT3DCSSUPPORT_API Bit_3DCS
{
public:
	// 构造空的坐标系
	Bit_3DCS(void);
	// 构造坐标系(由原点、向量一和向量一)
	Bit_3DCS( int n , Bit_Point3D OriginalPoint , Bit_Point3D One_AixV , Bit_Point3D Two_AixV );
	// 拷贝构造函数
	Bit_3DCS( const Bit_3DCS &cCS );
	// 重载"="等号
	Bit_3DCS& operator= (const Bit_3DCS& cCS );
	// 重载"=="恒等判断
	bool operator == (const Bit_3DCS& cCS )const;
	// 重载"!="恒等判断
	bool operator != (const Bit_3DCS& cCS )const;

	~Bit_3DCS(void);
	
	// 初始化设置
	void Set_Initial( const int& n , const Bit_Point3D& OriginalPoint 
		, const Bit_Point3D& One_AixV , const Bit_Point3D& Two_AixV );

	// 得到原点
	inline Bit_Point3D Get_OriginalPoint(void) const ;
	// 得到X轴向量
	inline Bit_Point3D Get_XAixVector(void) const ;
	// 得到Y轴向量
	inline Bit_Point3D Get_YAixVector(void) const ;
	// 得到Z轴向量
	inline Bit_Point3D Get_ZAixVector(void) const ;

	//根据给定B坐标系在A坐标系中的位置计算A坐标系中的点在B坐标系中点的坐标
	Bit_Point3D TransformCoordinateFromCSAToCSB( const Bit_Point3D& BCS_OriginInACS 
		, const Bit_Point3D& BCS_ZAxisVecInACS , const Bit_Point3D& BCS_XAxisVecInACS 
		, const Bit_Point3D& PointInACS) const ;

private:
	// 坐标原点
	Bit_Point3D OriginalPoint_;
	// X轴向量
	Bit_Point3D X_AixVector_;
	// Y轴向量
	Bit_Point3D Y_AixVector_;
	// Z轴向量
	Bit_Point3D Z_AixVector_;
};
#endif