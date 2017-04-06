//#pragma once

/********************************************************************
created:	2016/02/09
 
file base:	BIT_DAMAGESIMULATION_API
file ext:	h
author:		Xuyuxin

purpose:	�ı����浥Ԫ�Զ������ı����浥Ԫ

*********************************************************************/

#ifndef BITQUADMESHINGQ_H__
#define BITQUADMESHINGQ_H__

#include "Bit_Mesh_Global.h"
//�����嵥Ԫ
#include "BITMeshBase/Bit_EleSurQuad.h"
//����ϵ����
#include "BIT3DCSSupport/Bit_3DCS.h"
//��
#include "BITMeshBase/Bit_Line.h"
//�߶�
#include "BITSegmentSupport/Bit_3DSegmentDP.h"

class BITMESH_API Bit_QuadMeshingQ
{
public:
	Bit_QuadMeshingQ(void);
	// �����ʼ����Ԫ
	Bit_QuadMeshingQ( Bit_EleSurQuad EQ , int LineId );
	// �������캯��
	Bit_QuadMeshingQ( const Bit_QuadMeshingQ & cQMQ);
	// ����"="�Ⱥ�
	Bit_QuadMeshingQ& operator= (const Bit_QuadMeshingQ& cQMQ );
	// ����"=="�Ⱥ�
	bool operator == (const Bit_QuadMeshingQ& cQMQ )const;

	~Bit_QuadMeshingQ(void);

	// ��ó�ʼ�ı��ε�Ԫ
	inline Bit_EleSurQuad Get_InQuadElement(void) const;
	// ��õ�Ԫ����ϵ
	inline Bit_3DCS Get_CSInElement(void) const;
	// ��õ�Ԫ�ϵ���
	inline void Get_LineInElement( Bit_Line LineInE[4] ) const;
	// �����0��2�ϻ������������
	inline int Get_DividNInLine02( void )const;
	// �����1��3�ϻ������������
	inline int Get_DividNInLine13( void )const;
	// ��������Ƿ��ѽ��л���
	inline bool Get_IfDivid(void)const;
	// ��õ�Ԫ�ϵĽڵ���
	inline int Get_NodeNumber(void)const;
	// ��õ�Ԫ�ϵĵ�Ԫ��
	inline int Get_ElementNumber(void)const;
	// ��õ�Ԫ�Ͻڵ�
	void Get_NodeInElement( int * NodeNumber , Bit_Node N[] )const;
	// ��õ�Ԫ�ϵ�Ԫ
	void Get_ElementInElement( int * ElementNumber , Bit_EleSurQuad E[] )const;

	// �õ�02��֮��(��)�Ĵ�Ԫ
	void Get_ElementIn02( const int& FristNum_Element , Bit_EleSurQuad E[] );
	// �õ�02��֮���i(��)�ĵ�Ԫ(i��0��ʼ)
	void Get_iElementGIn02( const int& i , Bit_EleSurQuad E[] );

	//�����ı������񻮷֣��õ���Ԫ���ڵ�Ԫ����ϵ�е����꣩
	void MeshQuad( const int& FristNum_Node, const int& FristNum_Element 
		, const int& N_L02 , const int &N_L13);

private:
	// ��ʼ�ı��ε�Ԫ
	Bit_EleSurQuad Element_Quad_;
	// ��Ԫ����ϵ
	Bit_3DCS CS_E_;
	// ���嵥Ԫ�ϵ���
	Bit_Line LineInElement_[4];
	// 0��2���ϻ��ֵ�����
	int DividLine02_;
	// 1��3���ϻ��ֵ�����
	int DividLine13_;
	// �Ƿ��ѽ��������񻮷�
	bool IfDividFinished_;
	// ����ڵ����
	Bit_Node *NodeInElement_;
	// ��Ԫ����
	Bit_EleSurQuad *ElementInElement_;
};

#endif
