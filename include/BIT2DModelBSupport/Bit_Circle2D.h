//#pragma once
/********************************************************************
created:	2016/08/20
 
file base:	BIT_DAMAGESIMULATION_API
file ext:	h
author:		Xuyuxin

purpose:	2άԲ���ݽṹ

*********************************************************************/

#include "Bit_2DModelBSupport_Global.h"
#include "BITPointSupport/Bit_Point2D.h"

#ifndef BITCIRCLE2D_H__
#define BITCIRCLE2D_H__

class BIT2DMODELBSUPPORT_API Bit_Circle2D
{
public:
	// �պ���
	Bit_Circle2D(void);
	// �����ʼ������
	Bit_Circle2D( Bit_Point2D CentreP , double Radius );
	// �����ʼ����������Բ�ı�׼����X^2+y^2+Dx+Ey+F=0��Բ�ĵ�͹��Ͱ뾶
	Bit_Circle2D( double D , double E , double F );

	//�������캯��
	Bit_Circle2D( const Bit_Circle2D &cC2D );
	//���صȺ�
	Bit_Circle2D & operator = ( const Bit_Circle2D & cC2D );
	//���ص���
	bool operator == ( const Bit_Circle2D & cC2D ) const;
	//���ز�����
	bool operator != ( const Bit_Circle2D & cC2D ) const;

	~Bit_Circle2D(void);

	// ��ʼ������
	void Set_Initial( const Bit_Point2D& CentreP , const double& Radius );
	// �õ��Ƿ���
	inline bool Get_IfDefinition( void ) const;
	// �õ�Բ�ĵ�
	inline Bit_Point2D Get_CentreP( void ) const;
	// �õ�ֱ��
	inline double Get_Radius( void ) const;
	// �õ���׼�����̵�D
	inline double Get_StandardD( void ) const;
	// �õ���׼�����̵�E
	inline double Get_StandardE( void ) const;
	// �õ���׼�����̵�F
	inline double Get_StandardF( void ) const;
	// �жϵ��Ƿ���Բ��
	inline bool JudgePointIfInCircle( const Bit_Point2D & P )const;

private:
	// Բ�ĵ�
	Bit_Point2D CentreP_;
	// �뾶
	double Radius_;
	// Բ�Ƿ���
	bool IfDefinition_;
};
#endif
