//#pragma once
/********************************************************************
created:	2016/08/20
 
file base:	BIT_DAMAGESIMULATION_API
file ext:	h
author:		wangxiao

purpose:	2ά����������ݽṹ

*********************************************************************/

#include "Bit_PointSupport_Global.h"

#ifndef BITPLOLARPOINT2D_H__
#define BITPLOLARPOINT2D_H__


class BITPOINTSUPPORT_API Bit_PolarPoint2D
{
public:
	// ��
	Bit_PolarPoint2D(void);
	// �����ʼ����
	Bit_PolarPoint2D( double Radius, double AngleR );
	// �������캯��
	Bit_PolarPoint2D( const Bit_PolarPoint2D& cPP2D);

	// ��������
	~Bit_PolarPoint2D(void);

	// ���صȺ�
	Bit_PolarPoint2D& operator= (const Bit_PolarPoint2D& cPP2D );
	// ���ؼ���
	Bit_PolarPoint2D operator- (const Bit_PolarPoint2D& cPP2D )const;
	// ���ؼӺ�
	Bit_PolarPoint2D operator+ (const Bit_PolarPoint2D& cPP2D )const;
	// ���غ���ж�
	bool operator == (const Bit_PolarPoint2D& cPP2D )const;
	// ���ز����ж�
	bool operator != (const Bit_PolarPoint2D& cPP2D )const;

	//�������в���
	inline void Set_Initial( const double& Radius , const double& AngleR );
	//���þ������ֵ
	inline void Set_Radius(const double& Radius );
	//���ýǶ�(����)ֵ
	inline void Set_AngleR(const double& AngleR );

	// �õ����еľ������ֵ
	inline double Get_Radius(void) const ;
	// �õ����еĽǶ�(����)ֵ
	inline double Get_AngleR(void) const ;

private:
	double Radius_;
	double AngleR_;

};
#endif
