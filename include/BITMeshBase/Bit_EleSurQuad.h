//#pragma once
/********************************************************************
created:	2016/02/09
 
file base:	BIT_DAMAGESIMULATION_API
file ext:	h
author:		Xuyuxin

purpose:	四边形面单元及相关计算

*********************************************************************/

#ifndef BITELESURQUAD_H__
#define BITELESURQUAD_H__

#include "Bit_MeshBase_Global.h"
#include "Bit_Node.h"
#include "Bit_NodeCompute.h"
#include "BIT3DComputeSupport/Bit_3DCompute.h"
#include "BITMathSupport/Bit_AdvMathCompute.h"

class BITMESHBASE_API Bit_EleSurQuad
{
public:
	// 构造空函数
	Bit_EleSurQuad(void);
	// 构造初始化单元
	Bit_EleSurQuad( int Id , int PartId , Bit_Node N[4] , double Thickness );
	// 拷贝构造函数
	Bit_EleSurQuad( const Bit_EleSurQuad& cElement_Quad);
	// 重载“=”
	Bit_EleSurQuad& operator= (const Bit_EleSurQuad& cElement_Quad );
	// 重载“==”
	bool operator == (const Bit_EleSurQuad& cElement_Quad )const;
	// 析构函数
	~Bit_EleSurQuad(void);
	
	//***************设置四变形单元结构中的私有变量**************
	//// 初始化设置
	void Set_Initial( const int& Id , const int& PartId , const Bit_Node N[4] 
		, const double& Thickness );
	//设置Id值
	inline void Set_Id(const int& Id );
	//设置PartId值
	inline void Set_PartId(const int& PartId );
	//设置单元厚度
	inline void Set_Thickness(const int& Thickness );
	//设置四个节点的数组(只能通过初始进行设置)
	/*inline void Set_Bit_Node( const Bit_Node N[4] );*/

	//***************得到四变形单元结构中的私有变量**************
	//得到Id
	inline int Get_id( void ) const;
	//得到PartId值
	inline int Get_Partid( void ) const;
	//得到单元厚度
	inline double Get_Thickness( void ) const;
	//得到4个节点
	void Get_Node( Bit_Node N[4] )const;
	//得到N[0],第1个节点
	inline Bit_Node Get_Node_0( void )const; 
	//得到N[1],第2个节点
	inline Bit_Node Get_Node_1( void )const; 
	//得到N[2],第3个节点
	inline Bit_Node Get_Node_2( void )const; 
	//得到N[3],第4个节点
	inline Bit_Node Get_Node_3( void )const; 
	//得到是否构造成
	inline bool Get_IfPorduct(void)const;

	//得到标准法向量(按前3点计算)
	inline Bit_Point3D Get_StandardizationVector(void)const;

	//得到单元标准平面方程系数A(基于点0)
	inline double Get_PlaneFunctionCoefficient_A_OnN0(void)const;
	//得到单元标准平面方程系数B(基于点0)
	inline double Get_PlaneFunctionCoefficient_B_OnN0(void)const;
	//得到单元标准平面方程系数C(基于点0)
	inline double Get_PlaneFunctionCoefficient_C_OnN0(void)const;
	//得到单元标准平面方程系数D(基于点0)
	inline double Get_PlaneFunctionCoefficient_D_OnN0(void)const;
	//得到单元四个节点坐标的X值数组
	inline void Get_XArrayInBit_Node( double XInN[4])const;
	//得到单元四个节点坐标的Y值数组
	inline void Get_YArrayInBit_Node( double YInN[4])const;
	//得到单元四个节点坐标的Z值数组
	inline void Get_ZArrayInBit_Node( double ZInN[4])const;
	//得到单元中所有节点X的最大值
	double Get_X_Max(void)const;
	//得到单元中所有节点X的最小值
	double Get_X_Min(void)const;
	//得到单元中所有节点Y的最大值
	double Get_Y_Max(void)const;
	//得到单元中所有节点Y的最小值
	double Get_Y_Min(void)const;
	//得到单元中所有节点Z的最大值
	double Get_Z_Max(void)const;
	//得到单元中所有节点Z的最小值
	double Get_Z_Min(void)const;

private:
	// ID号
	int Id_;
	// 归属的PartId
	int PartId_;
	// 四个节点的数组
	Bit_Node N_[4];
	// 平面厚度
	double Thickness_;
	// 四个节点的单元是否生成
	bool IfPorduct_;
};

#endif
