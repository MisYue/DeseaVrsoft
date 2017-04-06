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

#ifndef BIT2DSEGMENT_H__
#define BIT2DSEGMENT_H__

class BITSEGMENTSUPPORT_API Bit_2DSegmentDP
{
public:
	Bit_2DSegmentDP(void);
	// �����ʼ���߶Σ���������㣨��㡢�յ㣩��
	Bit_2DSegmentDP( Bit_Point2D Point_Frist , Bit_Point2D Point_Sencod );
	//�������캯��
	Bit_2DSegmentDP( const Bit_2DSegmentDP &cS2D );
	//���ء�=��
	Bit_2DSegmentDP &operator=( const Bit_2DSegmentDP &cS2D );
	//���ء�==��
	bool operator == ( const Bit_2DSegmentDP & cS2D ) const;
	//���ء�!=��
	bool operator != ( const Bit_2DSegmentDP & cS2D ) const;

	~Bit_2DSegmentDP(void);

	//�õ���һ����
	inline Bit_Point2D Get_FristPoint(void) const;
	//�õ��ڶ�����
	inline Bit_Point2D Get_SencodPoint(void) const;
	//�õ���׼������
	inline Bit_Point2D Get_SVector(void) const;

private:
	// ��һ����
	Bit_Point2D Point_Frist_;
	// �ڶ�����
	Bit_Point2D Point_Sencod_;
	// ��׼������
	Bit_Point2D SVer_;
};
#endif
