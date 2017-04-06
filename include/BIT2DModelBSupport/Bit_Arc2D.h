/********************************************************************
created:	2016/08/20
 
file base:	BIT_DAMAGESIMULATION_API
file ext:	h
author:		Xuyuxin

purpose:	2άԲ�����ݽṹ

*********************************************************************/

#include "Bit_2DModelBSupport_Global.h"
#include "BITPointSupport/Bit_Point2D.h"
#include "BIT2DComputeSupport/Bit_2DCompute.h"

#ifndef BITARC2D_H__
#define BITARC2D_H__

class BIT2DMODELBSUPPORT_API Bit_Arc2D
{
public:
	Bit_Arc2D(void);
	// �����ʼ������
	Bit_Arc2D( Bit_Point2D CentreP , Bit_Point2D FristP , double Radian );

	//�������캯��
	Bit_Arc2D( const Bit_Arc2D &cA2D );
	//���صȺ�
	Bit_Arc2D & operator = ( const Bit_Arc2D & cA2D );
	//���غ����
	bool operator == ( const Bit_Arc2D & cA2D ) const;
	//���ز�����
	bool operator != ( const Bit_Arc2D & cA2D ) const;
	//��������
	~Bit_Arc2D(void);

	// ��ʼ������
	void Set_Initial( const Bit_Point2D& CentreP ,const Bit_Point2D &FristP ,const double &Radian );
	// �õ��Ƿ���
	inline bool Get_IfDefinition( void ) const;
	// �õ�Բ�ĵ�
	inline Bit_Point2D Get_CentreP( void ) const;
	// �õ�����
	inline double Get_Radian( void ) const;
	// �õ��뾶
	inline double Get_Radius( void ) const;
	// �õ���һ��
	inline Bit_Point2D Get_FirstP( void ) const;
	// �õ��ڶ���
	inline Bit_Point2D Get_SecondP( void ) const;
	// �жϵ��Ƿ���Բ����
	inline bool JudgePointIfInArc( const Bit_Point2D & P )const;

private:
	// Բ�ĵ�
	Bit_Point2D CentreP_;
	// �뾶
	double Radius_;
	// ��һ����
	Bit_Point2D FristP_;
	// ����(�ӵ�һ����ת������ʱ��Ϊ��,˳ʱ��Ϊ����0~2Pi����)
	double Radian_;
	// Բ���Ƿ���
	bool IfDefinition_;
};
#endif

