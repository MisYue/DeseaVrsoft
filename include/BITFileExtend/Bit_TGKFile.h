//#pragma once
//#pragma warning(disable:4251)
/********************************************************************
created:	2016/06/8
 
file base:	BIT_DAMAGESIMULATION_API
file ext:	h
author:		Xuyuxin

purpose:	TG�����K�ļ���ز���

*********************************************************************/

// ��̬�⵼��
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
	// �պ���
	Bit_TGKFile(void);
	// ��������
	~Bit_TGKFile(void);

	//�õ��ڵ���
	int GetNodeNumber( const string& Filepath )const;
	//�õ���Ԫ��
	int GetShellElementNumber( const string& Filepath )const ;
	//�õ����нڵ�
	void GetNode(const string& Filepath , vector< Bit_Node>*)const;
	//�õ����еĽڵ����Ԫ
	//void GetElement(const string& Filepath , vector< Bit_Node > Bit_Nodes 
	//	, vector< Bit_EleSurQuad > * )const;

private:
	//
	vector< Bit_Node *> * NodeVec_;
};
#endif
