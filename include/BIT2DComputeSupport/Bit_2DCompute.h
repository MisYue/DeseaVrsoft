/********************************************************************
created:	2016/08/24
 
file base:	BIT_DAMAGESIMULATION_API
file ext:	h
author:		wangxiao

purpose:	2维空间几何计算

*********************************************************************/

#include "Bit_2DComputeSupport_Global.h"
#include "BITPointSupport/Bit_Point2D.h"

#ifndef BIT2DCOMPUTE_H__
#define BIT2DCOMPUTE_H__

class BIT2DCOMPUTESUPPORT_API Bit_2DCompute
{
public:
	Bit_2DCompute(void);
	~Bit_2DCompute(void);

	//计算标准向量
	inline Bit_Point2D VectorStandardization( const Bit_Point2D &V )const;
	//计算向量的模
	inline double ComputeVectorLength( const Bit_Point2D &V )const;
	//求两个向量的点乘
	inline double ComputeDotProduct( const Bit_Point2D &P1 , const Bit_Point2D &P2 )const;
	//计算向量的数乘
	inline Bit_Point2D ComputeScalarMultiplication( const Bit_Point2D &V , const double &factor )const;
	//计算两点之间的距离
	inline double ComputeDis2Point( const Bit_Point2D &P1 , const Bit_Point2D &P2 )const;
	//计算点向量与X轴的夹角(输出弧度)
	inline double ComputeAnglePV_Xaxis( const Bit_Point2D &P )const;
	//计算两个向量间的夹角(输出弧度)
	inline double ComputeAngleTwoV( const Bit_Point2D &V1 , const Bit_Point2D &V2 )const;
	//计算任意两个向量的夹角(带方向，逆时针为正)
	inline double ComputeDAngleByTwoV( const Bit_Point2D &V1 , const Bit_Point2D &V2 ) const;
	//计算一个点绕原点一定角度后获得另一个点
	inline Bit_Point2D RotateAngleByOP( const Bit_Point2D &P , const double& angle )const; 

	

	//求两个向量的叉乘。平面向量的叉乘将会得到一个垂直该平面的向量(0,0,Z)，变成空间向量
	//因此这里结果为一个数值，意义为叉乘所得向量的Z坐标，绝对值是以两个向量为邻边的平行四边形面积
	inline double ComputeCrossProduct( Bit_Point2D &P1 , Bit_Point2D &P2 )const;
};
#endif
