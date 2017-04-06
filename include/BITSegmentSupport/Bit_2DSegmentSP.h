/********************************************************************
created:	2016/10/03
 
file base:	BIT_DAMAGESIMULATION_API
file ext:	h
author:		Xuyuxin

purpose:	2ά�߶����ݽṹ

*********************************************************************/

#include "Bit_SegmentSupport_Global.h"
#include "BITPointSupport/Bit_Point2D.h"
#include "BIT2DComputeSupport/Bit_2DCompute.h"

#ifndef BIT2DSEGMENTNEW_H__
#define BIT2DSEGMENTNEW_H__

class BITSEGMENTSUPPORT_API Bit_2DSegmentSP
{
public:
	Bit_2DSegmentSP(void);
	// �����ʼ���߶�
	Bit_2DSegmentSP( Bit_Point2D Point_Frist , Bit_Point2D SVer , double Length );
	//�������캯��
	Bit_2DSegmentSP( const Bit_2DSegmentSP &cS2D );
	//���ء�=��
	Bit_2DSegmentSP &operator=( const Bit_2DSegmentSP &cS2D );
	//���ء�==��
	bool operator == ( const Bit_2DSegmentSP & cS2D ) const;
	//���ء�!=��
	bool operator != ( const Bit_2DSegmentSP & cS2D ) const;

	~Bit_2DSegmentSP(void);

	//�õ���һ����
	inline Bit_Point2D Get_FristPoint(void) const;
	//�õ��ڶ�����
	inline Bit_Point2D Get_SencodPoint(void) const;
	//�õ���׼������
	inline Bit_Point2D Get_SVector(void) const;
	//�õ�����
	inline double Get_Length(void) const;

private:
	// ��һ����
	Bit_Point2D Point_Frist_;
	// ��׼����������
	Bit_Point2D SVer_;
	// �߶γ���
	double Length_;
};
#endif
