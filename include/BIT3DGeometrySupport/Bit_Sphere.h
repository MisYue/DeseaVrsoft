/********************************************************************
created:	2016/10/15
 
file base:	BIT_DAMAGESIMULATION_API
file ext:	h
author:		Xuyuxin

purpose:	3ά��(������Ŀ���Чģ��)

*********************************************************************/

#include "Bit_3DModelSupport_Global.h"
#include "MathCalculationSupport/CoordinatesPosition.h"
//#include "MathCalculationSupport/AdvancedMath.h"

#ifndef BITSPHERE_H__
#define BITSPHERE_H__

class BIT3DMODELSUPPORT_API Bit_Sphere
{
public: 
	//���캯��
	Bit_Sphere ( void );
	//��ʼ�����캯��
	Bit_Sphere ( CoordinatesPosition CP , double radius );
	//�����ʼ����������Բ�ı�׼����X^2+y^2+z^2+Dx+Ey+Fz+H=0��Բ�ĵ�͹��Ͱ뾶
	Bit_Sphere ( double D , double E , double F , double H );

	//�������캯��
	Bit_Sphere ( const Bit_Sphere &cSp );
	//�����=����
	Bit_Sphere &operator=( const Bit_Sphere &cSp );

	//���ó�ʼ��
	void Set_Initial_CPAndR( const CoordinatesPosition &CP , const	double &radius );

	//�õ���������
	inline CoordinatesPosition Get_CentrePoint( void )const;
	//�õ���İ뾶
	inline double Get_Radius( void )const;
	//�õ�D

	//�õ�E

	//

private:
	//��������
	CoordinatesPosition CP_;
	//��뾶
	double radius_;
};
#endif