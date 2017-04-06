/********************************************************************
created:	2016/10/03
 
file base:	BIT_DAMAGESIMULATION_API
file ext:	h
author:		Xuyuxin

purpose:	2ά�߶����ݽṹ

*********************************************************************/

#include "Bit_SegmentSupport_Global.h"
#include "BITPointSupport/Bit_Point3D.h"
#include "BIT3DComputeSupport/Bit_3DCompute.h"

#ifndef BIT3DSEGMENT_H__
#define BIT3DSEGMENT_H__

class BITSEGMENTSUPPORT_API Bit_3DSegmentDP
{
public:
	Bit_3DSegmentDP(void);
	// �����ʼ���߶Σ���������㣨��㡢�յ㣩��
	Bit_3DSegmentDP( Bit_Point3D Point_Frist , Bit_Point3D Point_Sencod );
	//�������캯��
	Bit_3DSegmentDP( const Bit_3DSegmentDP &cS3D );
	//���ء�=��
	Bit_3DSegmentDP &operator=( const Bit_3DSegmentDP &cS3D );
	//���ء�==��
	bool operator == ( const Bit_3DSegmentDP & cS3D ) const;
	//���ء�!=��
	bool operator != ( const Bit_3DSegmentDP & cS3D ) const;

	~Bit_3DSegmentDP(void);

	//�õ���һ����
	inline Bit_Point3D Get_FristPoint(void) const;
	//�õ��ڶ�����
	inline Bit_Point3D Get_SencodPoint(void) const;
	//�õ���׼������
	inline Bit_Point3D Get_SVector(void) const;

	////�ж�һ�����Ƿ����߶���
	bool JudgePointIfInSegment( const Bit_Point3D &Point)const;
	//// ���������߶εĽ�������(�����������߶��Ƿ���һ��ƽ���ϵļ�顢���������߶α�Ȼ�ཻ�н���)
	Bit_Point3D ComputePointBetween2Segments_NoCheck( const Bit_3DSegmentDP& S1 
		, const Bit_3DSegmentDP& S2 )const;

private:
	// ��һ����
	Bit_Point3D Point_Frist_;
	// �ڶ�����
	Bit_Point3D Point_Sencod_;
	// ��׼������
	Bit_Point3D SVer_;
};
#endif
