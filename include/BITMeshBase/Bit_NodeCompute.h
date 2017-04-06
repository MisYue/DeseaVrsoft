//#pragma once

/********************************************************************
created:	2016/12/21
 
file base:	BIT_DAMAGESIMULATION_API
file ext:	h
author:		Xuyuxin

purpose:	节点定义及相关计算函数

*********************************************************************/

#ifndef BITNODECOMPUTE_H__
#define BITNODECOMPUTE_H__

#include "Bit_MeshBase_Global.h"
#include "Bit_Node.h"
#include "BITMathSupport/Bit_AdvMathCompute.h"
#include "BIT3DComputeSupport/Bit_3DCompute.h"

class BITMESHBASE_API Bit_NodeCompute
{
public:
	Bit_NodeCompute(void);
	~Bit_NodeCompute(void);

	// 判断大于等于3个点是否共面，共面返回true，不共面返回flase
	bool JudgeIfCoplanarityForNPoints( const int& n , const Bit_Point3D Num[] )const;
	// 判断3个及以上节点（Node）是否在一个平面上（n<3退出程序）
	bool JudgeIfCoplanarityForNNodes( const int& n , const Bit_Node Nu[] )const;
};
#endif
