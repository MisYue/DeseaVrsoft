//#pragma once
//#pragma warning(disable:4251)
/********************************************************************
created:	2016/06/8
 
file base:	BIT_DAMAGESIMULATION_API
file ext:	h
author:		Xuyuxin

purpose:	TG输出的K文件相关操作

*********************************************************************/

// 动态库导出
#include "Bit_FileExtend_Global.h"
//
#include "BITMeshBase/Bit_Node.h"
#include "BITMeshBase/Bit_EleSurQuad.h"
#include "BITTransformSupport/Bit_TypeTransform.h"

#include <vector>
#include <map>
using namespace std;

#ifndef BITTGKFiLE_H__
#define BITTGKFiLE_H__

class BITFILEEXTEND_API Bit_TGKFile
{
public:
	// 空函数
	Bit_TGKFile(void);
	// 析构函数
	~Bit_TGKFile(void);

	//得到节点数
	int GetNodeNumber( const string& Filepath )const;
	//得到单元数
	int GetShellElementNumber( const string& Filepath )const ;
	//得到所有节点
	void GetNode(const string& Filepath , vector< Bit_Node>*)const;
	//得到所有的节点和面元
	//void GetElement(const string& Filepath , vector< Bit_Node > Bit_Nodes 
	//	, vector< Bit_EleSurQuad > * )const;

private:
	//
	vector< Bit_Node *> * NodeVec_;
};
#endif
