/********************************************************************
created:	2016/08/24
 
file base:	BIT_DAMAGESIMULATION_API
file ext:	h
author:		wangxiao

purpose:	2ά�ռ伸�μ���

*********************************************************************/

#include "Bit_2DComputeSupport_Global.h"
#include "BITPointSupport/Bit_Point2D.h"

#ifndef BIT2DCOMPUTE_H__
#define BIT2DCOMPUTE_H__

class BIT2DCOMPUTESUPPORT_API Bit_2DCompute
{
public:
	Bit_2DCompute(void);
	~Bit_2DCompute(void);

	//�����׼����
	inline Bit_Point2D VectorStandardization( const Bit_Point2D &V )const;
	//����������ģ
	inline double ComputeVectorLength( const Bit_Point2D &V )const;
	//�����������ĵ��
	inline double ComputeDotProduct( const Bit_Point2D &P1 , const Bit_Point2D &P2 )const;
	//��������������
	inline Bit_Point2D ComputeScalarMultiplication( const Bit_Point2D &V , const double &factor )const;
	//��������֮��ľ���
	inline double ComputeDis2Point( const Bit_Point2D &P1 , const Bit_Point2D &P2 )const;
	//�����������X��ļн�(�������)
	inline double ComputeAnglePV_Xaxis( const Bit_Point2D &P )const;
	//��������������ļн�(�������)
	inline double ComputeAngleTwoV( const Bit_Point2D &V1 , const Bit_Point2D &V2 )const;
	//�����������������ļн�(��������ʱ��Ϊ��)
	inline double ComputeDAngleByTwoV( const Bit_Point2D &V1 , const Bit_Point2D &V2 ) const;
	//����һ������ԭ��һ���ǶȺ�����һ����
	inline Bit_Point2D RotateAngleByOP( const Bit_Point2D &P , const double& angle )const; 

	

	//�����������Ĳ�ˡ�ƽ�������Ĳ�˽���õ�һ����ֱ��ƽ�������(0,0,Z)����ɿռ�����
	//���������Ϊһ����ֵ������Ϊ�������������Z���꣬����ֵ������������Ϊ�ڱߵ�ƽ���ı������
	inline double ComputeCrossProduct( Bit_Point2D &P1 , Bit_Point2D &P2 )const;
};
#endif
