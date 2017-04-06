/********************************************************************
created:	2016/10/07
 
file base:	BIT_DAMAGESIMULATION_API
file ext:	h
author:		Xuyuxin

purpose:	3维长方体(服务于目标等效模型)

*********************************************************************/
#include "Bit_3DGeometrySupport_Global.h"
#include "BITPointSupport/Bit_Point3D.h"
//#include "MathCalculationSupport/AdvancedMath.h"
#include "MathCalculationSupport/Node.h"
#include "MathCalculationSupport/Bit_Surface_Quad.h"

#ifndef BITCUBOID_H__
#define BITCUBOID_H__

class BIT3DMODELSUPPORT_API Bit_Cuboid
{
public:
	// 空构造函数
	Bit_Cuboid(void);
	// 初始化构造函数
	Bit_Cuboid( CoordinatesPosition CP , double XDLength
		, double YDLength , double ZDLength, int Num_NS , int Num_QS );
	// 拷贝构造函数
	Bit_Cuboid( const Bit_Cuboid &cCb );
	//重载等号
	Bit_Cuboid & operator = ( const Bit_Cuboid & cCb );
	//重载恒等于
	bool operator == ( const Bit_Cuboid & cCb ) const;
	//重载不等于
	bool operator != ( const Bit_Cuboid & cCb ) const;
	//析构函数
	~Bit_Cuboid(void);

	// 设置初始化
	void Set_Initial( const CoordinatesPosition& CP , const double& XDLength 
		, const double& YDLength , const double& ZDLength);
	// 得到中心点坐标
	inline CoordinatesPosition Get_CentrePoint( void )const;
	// 得到X方向长
	inline double Get_XDLength( void )const;
	// 得到Y方向长
	inline double Get_YDLength( void )const;
	// 得到Z方向长
	inline double Get_ZDLength( void )const;
	//得到4个节点
	void Get_Node( Node N[8] )const;
	//得到N[0],第1个节点
	inline Node Get_Node_0( void )const; 
	//得到N[1],第2个节点
	inline Node Get_Node_1( void )const; 
	//得到N[2],第3个节点
	inline Node Get_Node_2( void )const; 
	//得到N[3],第4个节点
	inline Node Get_Node_3( void )const; 
	//得到N[4],第5个节点
	inline Node Get_Node_4( void )const; 
	//得到N[5],第6个节点
	inline Node Get_Node_5( void )const; 
	//得到N[6],第7个节点
	inline Node Get_Node_6( void )const; 
	//得到N[7],第8个节点
	inline Node Get_Node_7( void )const;

	//得到6个面
	void Get_SQ( Bit_Surface_Quad SQ[6] )const;

	//得到SQ[0]，第1个面
	inline Bit_Surface_Quad Get_SQ_1( void )const;
	//得到SQ[1]，第2个面
	inline Bit_Surface_Quad Get_SQ_2( void )const;
	//得到SQ[2]，第3个面
	inline Bit_Surface_Quad Get_SQ_3( void )const;
	//得到SQ[3]，第4个面
	inline Bit_Surface_Quad Get_SQ_4( void )const;
	//得到SQ[4]，第5个面
	inline Bit_Surface_Quad Get_SQ_5( void )const;
	//得到SQ[5]，第6个面
	inline Bit_Surface_Quad Get_SQ_6( void )const;

private:
	// 中心点坐标
	CoordinatesPosition CP_;
	// X方向长
	double XDLength_;
	// Y方向长
	double YDLength_;
	// Z方向长
	double ZDLength_;
	// 八个节点的数组
	Node N_[8];
	// 六个可进行网格划分的面单元
	Bit_Surface_Quad SQ_[6];

};
#endif
