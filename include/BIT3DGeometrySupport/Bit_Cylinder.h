//#pragma once

/********************************************************************
created:	2016/10/07
 
file base:	BIT_DAMAGESIMULATION_API
file ext:	h
author:		Xuyuxin

purpose:	3άԲ����(������Ŀ���Чģ��)

*********************************************************************/
#include "MathCalculationSupport/CoordinatesPosition.h"
#include "Bit_3DModelSupport_Global.h"

#ifndef BITCYLINDER_H__
#define BITCYLINDER_H__

class BIT3DMODELSUPPORT_API Bit_Cylinder
{
public:
	// �պ���
	Bit_Cylinder(void);
	// ���캯��
	Bit_Cylinder( CoordinatesPosition CP , double radius , double High 
		, CoordinatesPosition CAxisV );
	// �������캯��
	Bit_Cylinder( const Bit_Cylinder &cCl );
	//���صȺ�
	Bit_Cylinder & operator = ( const Bit_Cylinder &cCl );
	//���غ����
	bool operator == ( const Bit_Cylinder &cCl ) const;
	//���ز�����
	bool operator != ( const Bit_Cylinder &cCl ) const;

	~Bit_Cylinder(void);

	// ���ó�ʼ��
	void Set_Initial( const CoordinatesPosition& CP , const double& radius 
		, const double& High, const CoordinatesPosition& CV );

	//�õ����ĵ�
	inline CoordinatesPosition Get_CP( void )const;
	//�õ��뾶
	inline double Get_radius( void )const;
	//�õ��߶�
	inline double Get_High( void )const;
	//�õ����ʸ������
	inline CoordinatesPosition Get_CAxisV( void )const;

private:
	// ���ĵ�����
	CoordinatesPosition CP_;
	//�뾶
	double radius_;
	//�߶�
	double High_;
	//���ʸ������
	CoordinatesPosition CAxisV_;
};
#endif
