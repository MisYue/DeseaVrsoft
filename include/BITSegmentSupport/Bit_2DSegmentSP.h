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

#ifndef BIT2DSEGMENTNEW_H__
#define BIT2DSEGMENTNEW_H__

class BITSEGMENTSUPPORT_API Bit_2DSegmentSP
{
public:
	Bit_2DSegmentSP(void);
	// 构造初始化线段
	Bit_2DSegmentSP( Bit_Point2D Point_Frist , Bit_Point2D SVer , double Length );
	//拷贝构造函数
	Bit_2DSegmentSP( const Bit_2DSegmentSP &cS2D );
	//重载“=”
	Bit_2DSegmentSP &operator=( const Bit_2DSegmentSP &cS2D );
	//重载“==”
	bool operator == ( const Bit_2DSegmentSP & cS2D ) const;
	//重载“!=”
	bool operator != ( const Bit_2DSegmentSP & cS2D ) const;

	~Bit_2DSegmentSP(void);

	//得到第一个点
	inline Bit_Point2D Get_FristPoint(void) const;
	//得到第二个点
	inline Bit_Point2D Get_SencodPoint(void) const;
	//得到标准化向量
	inline Bit_Point2D Get_SVector(void) const;
	//得到长度
	inline double Get_Length(void) const;

private:
	// 第一个点
	Bit_Point2D Point_Frist_;
	// 标准化方向向量
	Bit_Point2D SVer_;
	// 线段长度
	double Length_;
};
#endif
