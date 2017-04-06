//#pragma once
/********************************************************************
created:	2016/10/28
 
file base:	BIT_DAMAGESIMULATION_API
file ext:	h
author:		Xuyuxin

purpose:	3ά������(������Ŀ���Чģ��)

*********************************************************************/
#include "Bit_3DModelSupport_Global.h"
#include "MathCalculationSupport/CoordinatesPosition.h"

#ifndef BITSELFSPHERE_H__
#define BITSELFSPHERE_H__

class BIT3DMODELSUPPORT_API Bit_SelfSphere
{
public:
	// �պ���
	Bit_SelfSphere(void);
	// ��ʼ���캯��
	Bit_SelfSphere( CoordinatesPosition CP , double radius , CoordinatesPosition CV );
	// �������캯��
	Bit_SelfSphere( const Bit_SelfSphere &cSS );
	//���صȺ�
	Bit_SelfSphere & operator = ( const Bit_SelfSphere & cSS );
	//���غ����
	bool operator == ( const Bit_SelfSphere & cSS ) const;
	//���ز�����
	bool operator != ( const Bit_SelfSphere & cSS ) const;
	//��������
	~Bit_SelfSphere(void);

	// ���ó�ʼ��
	void Set_Initial( const CoordinatesPosition& CP , const double& radius 
		, const CoordinatesPosition& CV  );
	//�õ����ĵ�
	inline CoordinatesPosition Get_CP( void )const;
	//�õ���뾶
	inline double Get_radius( void )const;
	//�õ����ʸ������(ָ����)
	inline CoordinatesPosition Get_CV( void )const;

private:
	//��������
	CoordinatesPosition CP_;
	//��뾶
	double radius_;
	//���ʸ������(ָ����)
	CoordinatesPosition CAxisV_;
};
#endif
