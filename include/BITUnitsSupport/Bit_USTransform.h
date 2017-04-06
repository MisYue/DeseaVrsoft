//#pragma once
/********************************************************************
created:	2016/12/20
 
file base:	BIT_DAMAGESIMULATION_API
file ext:	h
author:		Xuyuxin

purpose:	��λϵת�����㺯��

*********************************************************************/

#ifndef BITUSTRANSFORM_H__
#define BITUSTRANSFORM_H__

#include "Bit_UnitSystem.h"

enum SUnitType
{
	Length,			//����
	Mass,			//����
	Time,			//ʱ��
	StrainRate,		//Ӧ����
	Density,		//�ܶ�
	Force,			//��
	Pressure,		//ѹǿ
	Energy,			//����
	Velocity,		//�ٶ�
	Area,			//���
	Volum,			//���
	ContrastDis,	//�ԱȾ���
	VRC,			//�ٶ�˥��ϵ��
};


class BITUNITSSUPPORT_API Bit_USTransform
{
public:
	Bit_USTransform(void);
	~Bit_USTransform(void);

	//**************����ֵ��ת��*****************
	double TransformValue(const Bit_UnitSystem& Old_us
		, const Bit_UnitSystem& New_us, const double& Value
		, const SUnitType& Type)const;
	
	//**************����ֵ��ת��*****************
	// 3D����ֵת��
	inline Bit_Point3D TransformPoint3D( const Bit_UnitSystem& Old_us 
		, const Bit_UnitSystem& New_us , const Bit_Point3D &P )const;
	// 2D����ֵת��
	inline Bit_Point2D TransformPoint2D( const Bit_UnitSystem& Old_us 
		, const Bit_UnitSystem& New_us , const Bit_Point2D &P )const;
};
#endif
