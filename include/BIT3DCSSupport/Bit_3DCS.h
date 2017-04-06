/********************************************************************
created:	2015/11/03
 
file base:	BIT_DAMAGESIMULATION_API
file ext:	h
author:		Xuyuxin

purpose:	����ϵ����

*********************************************************************/

#ifndef BIT3DCS_H__
#define BIT3DCS_H__

#include "Bit_3DCSSupport_Global.h"
// ��ά����
#include "BITPointSupport/Bit_Point3D.h"
// �ռ伸�μ�����
#include "BIT3DComputeSupport/Bit_3DCompute.h"
//��ѧ������
#include "BITMathSupport/Bit_AdvMathCompute.h"

class BIT3DCSSUPPORT_API Bit_3DCS
{
public:
	// ����յ�����ϵ
	Bit_3DCS(void);
	// ��������ϵ(��ԭ�㡢����һ������һ)
	Bit_3DCS( int n , Bit_Point3D OriginalPoint , Bit_Point3D One_AixV , Bit_Point3D Two_AixV );
	// �������캯��
	Bit_3DCS( const Bit_3DCS &cCS );
	// ����"="�Ⱥ�
	Bit_3DCS& operator= (const Bit_3DCS& cCS );
	// ����"=="����ж�
	bool operator == (const Bit_3DCS& cCS )const;
	// ����"!="����ж�
	bool operator != (const Bit_3DCS& cCS )const;

	~Bit_3DCS(void);
	
	// ��ʼ������
	void Set_Initial( const int& n , const Bit_Point3D& OriginalPoint 
		, const Bit_Point3D& One_AixV , const Bit_Point3D& Two_AixV );

	// �õ�ԭ��
	inline Bit_Point3D Get_OriginalPoint(void) const ;
	// �õ�X������
	inline Bit_Point3D Get_XAixVector(void) const ;
	// �õ�Y������
	inline Bit_Point3D Get_YAixVector(void) const ;
	// �õ�Z������
	inline Bit_Point3D Get_ZAixVector(void) const ;

	//���ݸ���B����ϵ��A����ϵ�е�λ�ü���A����ϵ�еĵ���B����ϵ�е������
	Bit_Point3D TransformCoordinateFromCSAToCSB( const Bit_Point3D& BCS_OriginInACS 
		, const Bit_Point3D& BCS_ZAxisVecInACS , const Bit_Point3D& BCS_XAxisVecInACS 
		, const Bit_Point3D& PointInACS) const ;

private:
	// ����ԭ��
	Bit_Point3D OriginalPoint_;
	// X������
	Bit_Point3D X_AixVector_;
	// Y������
	Bit_Point3D Y_AixVector_;
	// Z������
	Bit_Point3D Z_AixVector_;
};
#endif