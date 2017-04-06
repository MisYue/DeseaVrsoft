//#pragma once

/********************************************************************
created:	2016/12/21
 
file base:	BIT_DAMAGESIMULATION_API
file ext:	h
author:		Xuyuxin

purpose:	�ڵ㶨�弰��ؼ��㺯��

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

	// �жϴ��ڵ���3�����Ƿ��棬���淵��true�������淵��flase
	bool JudgeIfCoplanarityForNPoints( const int& n , const Bit_Point3D Num[] )const;
	// �ж�3�������Ͻڵ㣨Node���Ƿ���һ��ƽ���ϣ�n<3�˳�����
	bool JudgeIfCoplanarityForNNodes( const int& n , const Bit_Node Nu[] )const;
};
#endif
