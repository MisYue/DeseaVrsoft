/********************************************************************
created:	2016/10/03
 
file base:	BIT_DAMAGESIMULATION_API
file ext:	h
author:		Xuyuxin

purpose:	3ά�߶����ݽṹ

*********************************************************************/

#include "Bit_SegmentSupport_Global.h"
#include "BITPointSupport/Bit_Point3D.h"
#include "BIT3DComputeSupport/Bit_3DCompute.h"

#ifndef BIT3DSEGMENTNEW_H__
#define BIT3DSEGMENTNEW_H__

class BITSEGMENTSUPPORT_API Bit_3DSegmentSP
{
public:
	Bit_3DSegmentSP(void);
	// �����ʼ���߶�
	Bit_3DSegmentSP( Bit_Point3D Point_Frist , Bit_Point3D SVer , double Length );
	//�������캯��
	Bit_3DSegmentSP( const Bit_3DSegmentSP &cS2D );
	//���ء�=��
	Bit_3DSegmentSP &operator=( const Bit_3DSegmentSP &cS2D );
	//���ء�==��
	bool operator == ( const Bit_3DSegmentSP & cS2D ) const;
	//���ء�!=��
	bool operator != ( const Bit_3DSegmentSP & cS2D ) const;

	~Bit_3DSegmentSP(void);

	//�õ���һ����
	inline Bit_Point3D Get_FristPoint(void) const;
	//�õ��ڶ�����
	inline Bit_Point3D Get_SencodPoint(void) const;
	//�õ���׼������
	inline Bit_Point3D Get_SVector(void) const;
	//�õ�����
	inline double Get_Length(void) const;

private:
	// ��һ����
	Bit_Point3D Point_Frist_;
	// ��׼����������
	Bit_Point3D SVer_;
	// �߶γ���
	double Length_;
};
#endif
