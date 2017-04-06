//#pragma once

/********************************************************************
created:	2016/02/09
 
file base:	BIT_DAMAGESIMULATION_API
file ext:	h
author:		Xuyuxin

purpose:	四边形面单元自动划分四变形面单元

*********************************************************************/

#ifndef BITQUADMESHINGQ_H__
#define BITQUADMESHINGQ_H__

#include "Bit_Mesh_Global.h"
//四面体单元
#include "BITMeshBase/Bit_EleSurQuad.h"
//坐标系定义
#include "BIT3DCSSupport/Bit_3DCS.h"
//线
#include "BITMeshBase/Bit_Line.h"
//线段
#include "BITSegmentSupport/Bit_3DSegmentDP.h"

class BITMESH_API Bit_QuadMeshingQ
{
public:
	Bit_QuadMeshingQ(void);
	// 构造初始化单元
	Bit_QuadMeshingQ( Bit_EleSurQuad EQ , int LineId );
	// 拷贝构造函数
	Bit_QuadMeshingQ( const Bit_QuadMeshingQ & cQMQ);
	// 重载"="等号
	Bit_QuadMeshingQ& operator= (const Bit_QuadMeshingQ& cQMQ );
	// 重载"=="等号
	bool operator == (const Bit_QuadMeshingQ& cQMQ )const;

	~Bit_QuadMeshingQ(void);

	// 获得初始四边形单元
	inline Bit_EleSurQuad Get_InQuadElement(void) const;
	// 获得单元坐标系
	inline Bit_3DCS Get_CSInElement(void) const;
	// 获得单元上的线
	inline void Get_LineInElement( Bit_Line LineInE[4] ) const;
	// 获得线0和2上划分网格的数量
	inline int Get_DividNInLine02( void )const;
	// 获得线1和3上划分网格的数量
	inline int Get_DividNInLine13( void )const;
	// 获得网格是否已进行划分
	inline bool Get_IfDivid(void)const;
	// 获得单元上的节点数
	inline int Get_NodeNumber(void)const;
	// 获得单元上的单元数
	inline int Get_ElementNumber(void)const;
	// 获得单元上节点
	void Get_NodeInElement( int * NodeNumber , Bit_Node N[] )const;
	// 获得单元上单元
	void Get_ElementInElement( int * ElementNumber , Bit_EleSurQuad E[] )const;

	// 得到02线之间(块)的大单元
	void Get_ElementIn02( const int& FristNum_Element , Bit_EleSurQuad E[] );
	// 得到02线之间第i(块)的单元(i从0开始)
	void Get_iElementGIn02( const int& i , Bit_EleSurQuad E[] );

	//进行四边形网格划分（得到单元是在单元坐标系中的坐标）
	void MeshQuad( const int& FristNum_Node, const int& FristNum_Element 
		, const int& N_L02 , const int &N_L13);

private:
	// 初始四边形单元
	Bit_EleSurQuad Element_Quad_;
	// 单元坐标系
	Bit_3DCS CS_E_;
	// 定义单元上的线
	Bit_Line LineInElement_[4];
	// 0、2线上划分的数量
	int DividLine02_;
	// 1、3线上划分的数量
	int DividLine13_;
	// 是否已进行了网格划分
	bool IfDividFinished_;
	// 网格节点矩阵
	Bit_Node *NodeInElement_;
	// 单元矩阵
	Bit_EleSurQuad *ElementInElement_;
};

#endif
