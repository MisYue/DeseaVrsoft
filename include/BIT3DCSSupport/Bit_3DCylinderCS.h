//
/********************************************************************
created:	2016/03/19
 
file base:	BIT_DAMAGESIMULATION_API
file ext:	h
author:		Xuyuxin

purpose:	��������ϵ�Ķ���

*********************************************************************/

#ifndef BITCYLINDERCOSYSTEM_H__
#define BITCYLINDERCOSYSTEM_H__


// ��̬�⵼��
#include "Bit_3DCSSupport_Global.h"
// ֱ����������ϵ��
#include "Bit_3DCS.h"

#include "BITPointSupport/Bit_Point3D.h"

#include "BIT3DComputeSupport/Bit_3DCompute.h"

class BIT3DCSSUPPORT_API Bit_3DCylinderCS
{
public:
	// �չ��캯��
	Bit_3DCylinderCS(void);
	// ��ʼ���캯��
	Bit_3DCylinderCS( Bit_Point3D OriginalPoint 
		, Bit_Point3D Polar_Vector , Bit_Point3D Z_Vector );

	// �������캯��
	Bit_3DCylinderCS( const Bit_3DCylinderCS &cCCS );
	// ����"="�Ⱥ�
	Bit_3DCylinderCS& operator= (const Bit_3DCylinderCS& cCCS );
	// ����"=="����ж�
	bool operator == (const Bit_3DCylinderCS& cCCS )const;

	~Bit_3DCylinderCS(void);

	// ��ʼ������
	void Set_Initial( const Bit_Point3D& OriginalPoint 
		, const Bit_Point3D& Polar_Vector ,const Bit_Point3D& Z_Vector);
	
	//�ռ�����ϵת������������ϵ
	void TransformFromCSToCCS( const int &XorY , const Bit_3DCS &CP_CS );
	//�ռ�����ϵ(ָ��)ת������������ϵ
	void TransformFromCS_PToCCS( const int &XorY , const Bit_3DCS *CP_CS );
	
	// �õ�ԭ��
	inline Bit_Point3D Get_OriginalPoint(void) const ;
	// �õ���������
	inline Bit_Point3D Get_PolarAixVector(void) const ;
	// �õ�Z������
	inline Bit_Point3D Get_ZAixVector(void) const;
	

private:
	// ����ԭ��
	Bit_Point3D OriginalPoint_;
	// ��������
	Bit_Point3D Polar_AixVector_;
	// Z������
	Bit_Point3D Z_AixVector_;
};

#endif

