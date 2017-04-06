/********************************************************************
created:	2016/10/03
 
file base:	BIT_DAMAGESIMULATION_API
file ext:	h
author:		Xuyuxin

purpose:	2维线段数据结构

*********************************************************************/

#include "Bit_SegmentSupport_Global.h"
#include "BITPointSupport/Bit_Point2D.h"
#include "BIT2DComputeSupport/Bit_2DCompute.h"

#ifndef BIT2DSEGMENT_H__
#define BIT2DSEGMENT_H__

class BITSEGMENTSUPPORT_API Bit_2DSegmentDP
{
public:
	Bit_2DSegmentDP(void);
	// 构造初始化线段（两个坐标点（起点、终点））
	Bit_2DSegmentDP( Bit_Point2D Point_Frist , Bit_Point2D Point_Sencod );
	//拷贝构造函数
	Bit_2DSegmentDP( const Bit_2DSegmentDP &cS2D );
	//重载“=”
	Bit_2DSegmentDP &operator=( const Bit_2DSegmentDP &cS2D );
	//重载“==”
	bool operator == ( const Bit_2DSegmentDP & cS2D ) const;
	//重载“!=”
	bool operator != ( const Bit_2DSegmentDP & cS2D ) const;

	~Bit_2DSegmentDP(void);

	//得到第一个点
	inline Bit_Point2D Get_FristPoint(void) const;
	//得到第二个点
	inline Bit_Point2D Get_SencodPoint(void) const;
	//得到标准化向量
	inline Bit_Point2D Get_SVector(void) const;

private:
	// 第一个点
	Bit_Point2D Point_Frist_;
	// 第二个点
	Bit_Point2D Point_Sencod_;
	// 标准化向量
	Bit_Point2D SVer_;
};
#endif
