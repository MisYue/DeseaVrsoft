/********************************************************************
created:	2015/11/03
 
file base:	BIT_DAMAGESIMULATION_API
file ext:	h
author:		Xuyuxin

purpose:	���пռ伸����ؼ���

*********************************************************************/

//#pragma once
#include "Bit_3DComputeSupport_Global.h"
//3D����
#include "BITPointSupport/Bit_Point3D.h"
//�ߵ���ѧ��
#include "BITMathSupport/Bit_AdvMathCompute.h"
//
//#include "Surface.h"

#ifndef BIT3DCOMPUTE_H__
#define BIT3DCOMPUTE_H__
//#define pi 3.14159265358979323846			//����Piֵ = 3.1415926

class BIT3DCOMPUTESUPPORT_API Bit_3DCompute
{
public:
	Bit_3DCompute(void);
	~Bit_3DCompute(void);

	//��������֮��ľ���
	inline double ComputeDistanceOf2Points( const Bit_Point3D &P1 , const Bit_Point3D &P2 )const;
	//************�ռ��ά�߶μ���***************
	//1.���������ߵķ������ռ��������ߵ���Ǽнǣ��������
	double AcuteAngleInTwoLine( const double& lineone_i , const double& lineone_j , 
		const double& lineone_k , const double& linetwo_i , const double& linetwo_j , const double& linetwo_k ) const;
	// ���������ߵķ������ռ��������ߵļнǣ��������
	double AngleInTwoLine( const double& lineone_i , const double& lineone_j , 
		const double& lineone_k , const double& linetwo_i , const double& linetwo_j , const double& linetwo_k ) const;
	//����������������������Ǽнǣ��������
	inline double AcuteAngleInTwoVetor( const Bit_Point3D &V1 , const Bit_Point3D &V2) const;
	//��������������������нǣ��������
	inline double AngleInTwoVetor( const Bit_Point3D &V1 , const Bit_Point3D &V2) const;

	//2.�ж�һ�����ϵ���������һ�����Ƿ���������֮��
	bool JudgePointSiteBetweenTwoPoint( const Bit_Point3D& JudgePoint ,
		const Bit_Point3D& FristPoint, const Bit_Point3D& SecondPoint) const;

	// �жϿռ�����ֱ���Ƿ��ཻ
	bool JudgeIfIntereFor2Lines( const Bit_Point3D &Ponint_one ,const Bit_Point3D &Ponint_two
		, const Bit_Point3D &Vector_one , const Bit_Point3D &Vector_two )const;

	//3.����ռ�����ֱ�ߵĽ��㣨ֱ����һ�����ֱ�������ķ�ʽ������
	bool  ComputeIntersectionPointToTwoLine(const Bit_Point3D &Ponint_one 
		,const Bit_Point3D &Ponint_two, const Bit_Point3D &Vector_one 
		, const Bit_Point3D &Vector_two , Bit_Point3D *InterePoint ) const;
	//4.�ɿռ���1���㡢�������̷������ͽؾ������һ��
	Bit_Point3D GetAnotherPoint(const Bit_Point3D& p1  
		, const double& aa , const double &bb , const double& cc , const double& dis) const;
	//5.�ж��������Ƿ���һ��ֱ����
	bool JudgeIfLineFor3Points( const Bit_Point3D &P1 , const Bit_Point3D &P2 , const Bit_Point3D &P3 ) const;
	// �ж�һ������һ����������
	bool JudgeIfPointInTriangle( const Bit_Point3D &JP , const Bit_Point3D &P1 
		, const Bit_Point3D &P2 , const Bit_Point3D &P3  )const;
	// �ж��ĸ�����ɵ��ı����Ƿ���͹�ı���
	bool JudgeIfConvexQuadOn4Points( const Bit_Point3D P[4] )const;
	
	// �ж�4�������Ƿ���3���㹲�ߵ�(��������)
	bool JudgeIf3PointsIn1LineFor4Points( const Bit_Point3D P[4])const;
	// �ж�4�������Ƿ���3���㹲�ߵ�(4������)
	bool JudgeIf3PointsIn1LineFor4Points( const Bit_Point3D& P0 ,const Bit_Point3D& P1
		, const Bit_Point3D& P2 ,const Bit_Point3D& P3)const;

	//***********************�ռ���������***************
	// ������λ������
	inline Bit_Point3D VectorStandardization( const Bit_Point3D &V )const;
	// ����������ģ
	inline double ComputeVectorLength( const Bit_Point3D &V )const;
	//6.�������������Ĳ��
	inline Bit_Point3D ComputeCrossProducts( const Bit_Point3D &V1 , const Bit_Point3D &V2 )const;
	//7. ���������������ĵ��
	inline double ComputeDotProducts( const Bit_Point3D &V1 , const Bit_Point3D &V2 )const;
	//��������������
	inline Bit_Point3D ComputeScalarMultiplication( const Bit_Point3D &V , const double &factor )const;
	//���������������㷨���������ط�����
	inline Bit_Point3D NormalVectorOn2Vectors( const Bit_Point3D &V1 , const Bit_Point3D &V2 )const;

	//8.ͨ�����������ƽ��ķ�����VV�����ط�����
	Bit_Point3D NormalVectorOn3points( const Bit_Point3D &P1 , const Bit_Point3D &P2 , const Bit_Point3D &P3 ) const;
	//9. ͨ��������������ƽ��ķ�����VV�����ط�����
	Bit_Point3D NormalVectorOnNpoints( int &n , const Bit_Point3D Num[] )const;
	//10.�жϿռ��ĵ��Ƿ��棬���淵��true�������淵��flase
	bool JudgeIfCoplanarityFor4Points( const Bit_Point3D& P1 , const Bit_Point3D& P2
		, const Bit_Point3D& P3 , const Bit_Point3D& P4)const;
	//11. �жϴ��ڵ���3�����Ƿ��棬���淵��true�������淵��flase
	bool JudgeIfCoplanarityForNPoints( const int& n , const Bit_Point3D Num[] )const;
	
	//******************���νṹ�������*******************
	//13.����Բ̨����������ڼ�����������
	//R����Բ�뾶��r��СԲ�뾶��H����
	inline double ComputeFrustumOfAConeVolume( const double& R , const double& r , const double& H ) const;
	//14.�����Բ̨����������ڼ�����������
	//R����Բ�뾶��r��СԲ�뾶��H����
	inline double ComputeHalfFrustumOfAConeVolume( const double& R , const double& r , const double& H ) const;
	//15.����Բ�������������ڼ�����������
	//Diameter��Բֱ����Height����
	inline double ComputeCylinderVolume( const double& Diameter , const double& Height ) const;
	//16.�����Բ�������������ڼ�����������
	//Diameter��Բֱ����Height����
	inline double ComputeHalfCylinderVolume( const double& Diameter , const double& Height ) const;
	//17.����Բ׶�����������ڼ�����������
	//Radius����Բ�뾶��Height����
	inline double ComputeConeVolume( const double& Radius , const double& Height ) const;
	//18.�����Բ׶�����������ڼ�����������
	//Radius����Բ�뾶��Height����
	inline double ComputeHalfConeVolume( const double& Radius , const double& Height )const;
	//19.����������������ڼ�����������
	inline double ComputeSphereVolume( const double& Diameter )const;
	//20.���㳤�������������ڼ�����������
	inline double ComputeCuboidVolume( const double& XLength , const double& YLength , const double& ZLength )const;

	///******************�������������*******************
	//21.�������(�����������ܶ�)
	//Mass��������g��Density���ܶȣ�g/cm^3
	inline double ComputeVolumeOnMassAndDensity( const double& Mass , const double& Density )const;

	//******************��������㼸��������*******************
	//22.�������������뾶
	inline double ComputeSphereRadiusOnVolume( const double& Volume )const;
};
#endif
//}

