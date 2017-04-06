/********************************************************************
created:	2016/10/03
 
file base:	BIT_DAMAGESIMULATION_API
file ext:	h
author:		Xuyuxin

purpose:	2维线段数据结构

*********************************************************************/

#include "Bit_SegmentSupport_Global.h"
#include "BITPointSupport/Bit_Point3D.h"
#include "BIT3DComputeSupport/Bit_3DCompute.h"

#ifndef BIT3DSEGMENT_H__
#define BIT3DSEGMENT_H__

class BITSEGMENTSUPPORT_API Bit_3DSegmentDP
{
public:
	Bit_3DSegmentDP(void);
	// 构造初始化线段（两个坐标点（起点、终点））
	Bit_3DSegmentDP( Bit_Point3D Point_Frist , Bit_Point3D Point_Sencod );
	//拷贝构造函数
	Bit_3DSegmentDP( const Bit_3DSegmentDP &cS3D );
	//重载“=”
	Bit_3DSegmentDP &operator=( const Bit_3DSegmentDP &cS3D );
	//重载“==”
	bool operator == ( const Bit_3DSegmentDP & cS3D ) const;
	//重载“!=”
	bool operator != ( const Bit_3DSegmentDP & cS3D ) const;

	~Bit_3DSegmentDP(void);

	//得到第一个点
	inline Bit_Point3D Get_FristPoint(void) const;
	//得到第二个点
	inline Bit_Point3D Get_SencodPoint(void) const;
	//得到标准化向量
	inline Bit_Point3D Get_SVector(void) const;

	////判断一个点是否在线段上
	bool JudgePointIfInSegment( const Bit_Point3D &Point)const;
	//// 计算两个线段的交点坐标(不进行两个线段是否在一个平面上的检查、而且两个线段必然相交有交点)
	Bit_Point3D ComputePointBetween2Segments_NoCheck( const Bit_3DSegmentDP& S1 
		, const Bit_3DSegmentDP& S2 )const;

private:
	// 第一个点
	Bit_Point3D Point_Frist_;
	// 第二个点
	Bit_Point3D Point_Sencod_;
	// 标准化向量
	Bit_Point3D SVer_;
};
#endif
