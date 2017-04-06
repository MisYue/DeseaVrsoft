//#pragma once
/********************************************************************
created:	2016/02/09
 
file base:	BIT_DAMAGESIMULATION_API
file ext:	h
author:		Xuyuxin

purpose:	�ı����浥Ԫ����ؼ���

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
	// ����պ���
	Bit_EleSurQuad(void);
	// �����ʼ����Ԫ
	Bit_EleSurQuad( int Id , int PartId , Bit_Node N[4] , double Thickness );
	// �������캯��
	Bit_EleSurQuad( const Bit_EleSurQuad& cElement_Quad);
	// ���ء�=��
	Bit_EleSurQuad& operator= (const Bit_EleSurQuad& cElement_Quad );
	// ���ء�==��
	bool operator == (const Bit_EleSurQuad& cElement_Quad )const;
	// ��������
	~Bit_EleSurQuad(void);
	
	//***************�����ı��ε�Ԫ�ṹ�е�˽�б���**************
	//// ��ʼ������
	void Set_Initial( const int& Id , const int& PartId , const Bit_Node N[4] 
		, const double& Thickness );
	//����Idֵ
	inline void Set_Id(const int& Id );
	//����PartIdֵ
	inline void Set_PartId(const int& PartId );
	//���õ�Ԫ���
	inline void Set_Thickness(const int& Thickness );
	//�����ĸ��ڵ������(ֻ��ͨ����ʼ��������)
	/*inline void Set_Bit_Node( const Bit_Node N[4] );*/

	//***************�õ��ı��ε�Ԫ�ṹ�е�˽�б���**************
	//�õ�Id
	inline int Get_id( void ) const;
	//�õ�PartIdֵ
	inline int Get_Partid( void ) const;
	//�õ���Ԫ���
	inline double Get_Thickness( void ) const;
	//�õ�4���ڵ�
	void Get_Node( Bit_Node N[4] )const;
	//�õ�N[0],��1���ڵ�
	inline Bit_Node Get_Node_0( void )const; 
	//�õ�N[1],��2���ڵ�
	inline Bit_Node Get_Node_1( void )const; 
	//�õ�N[2],��3���ڵ�
	inline Bit_Node Get_Node_2( void )const; 
	//�õ�N[3],��4���ڵ�
	inline Bit_Node Get_Node_3( void )const; 
	//�õ��Ƿ����
	inline bool Get_IfPorduct(void)const;

	//�õ���׼������(��ǰ3�����)
	inline Bit_Point3D Get_StandardizationVector(void)const;

	//�õ���Ԫ��׼ƽ�淽��ϵ��A(���ڵ�0)
	inline double Get_PlaneFunctionCoefficient_A_OnN0(void)const;
	//�õ���Ԫ��׼ƽ�淽��ϵ��B(���ڵ�0)
	inline double Get_PlaneFunctionCoefficient_B_OnN0(void)const;
	//�õ���Ԫ��׼ƽ�淽��ϵ��C(���ڵ�0)
	inline double Get_PlaneFunctionCoefficient_C_OnN0(void)const;
	//�õ���Ԫ��׼ƽ�淽��ϵ��D(���ڵ�0)
	inline double Get_PlaneFunctionCoefficient_D_OnN0(void)const;
	//�õ���Ԫ�ĸ��ڵ������Xֵ����
	inline void Get_XArrayInBit_Node( double XInN[4])const;
	//�õ���Ԫ�ĸ��ڵ������Yֵ����
	inline void Get_YArrayInBit_Node( double YInN[4])const;
	//�õ���Ԫ�ĸ��ڵ������Zֵ����
	inline void Get_ZArrayInBit_Node( double ZInN[4])const;
	//�õ���Ԫ�����нڵ�X�����ֵ
	double Get_X_Max(void)const;
	//�õ���Ԫ�����нڵ�X����Сֵ
	double Get_X_Min(void)const;
	//�õ���Ԫ�����нڵ�Y�����ֵ
	double Get_Y_Max(void)const;
	//�õ���Ԫ�����нڵ�Y����Сֵ
	double Get_Y_Min(void)const;
	//�õ���Ԫ�����нڵ�Z�����ֵ
	double Get_Z_Max(void)const;
	//�õ���Ԫ�����нڵ�Z����Сֵ
	double Get_Z_Min(void)const;

private:
	// ID��
	int Id_;
	// ������PartId
	int PartId_;
	// �ĸ��ڵ������
	Bit_Node N_[4];
	// ƽ����
	double Thickness_;
	// �ĸ��ڵ�ĵ�Ԫ�Ƿ�����
	bool IfPorduct_;
};

#endif
