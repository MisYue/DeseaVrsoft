/********************************************************************
created:	2016/03/19
 
file base:	BIT_DAMAGESIMULATION_API
file ext:	h
author:		Xuyuxin

purpose:	Բ������ϵ�������

*********************************************************************/
#ifndef BITCYLINDERPOINT3D_H__
#define BITCYLINDERPOINT3D_H__

// ��̬�⵼��
#include "Bit_PointSupport_Global.h"

class BITPOINTSUPPORT_API Bit_CylinderPoint3D
{
public:
	Bit_CylinderPoint3D(void);
	// ��ʼ�����캯��
	Bit_CylinderPoint3D( double Radius, double AngleR, double z );
	// �������캯��
	Bit_CylinderPoint3D( const Bit_CylinderPoint3D& cCCPositon);

	// ���صȺ�
	Bit_CylinderPoint3D& operator= (const Bit_CylinderPoint3D& cCCPositon );
	// ���ؼ���
	Bit_CylinderPoint3D operator- (const Bit_CylinderPoint3D& cCCPositon )const;
	// ���ؼӺ�
	Bit_CylinderPoint3D operator+ (const Bit_CylinderPoint3D& cCCPositon )const;
	// ���غ���ж�
	bool operator == (const Bit_CylinderPoint3D& cCCPositon )const;
	// ���ز����ж�
	bool operator != (const Bit_CylinderPoint3D& cCCPositon )const;

	~Bit_CylinderPoint3D(void);

	//�������в���
	inline void Set_Initial( const double& Radius , const double& AngleR ,const double& z);

	//���þ������ֵ
	inline void Set_Radius(const double& Radius );
	//���ýǶ�(����)ֵ
	inline void Set_AngleR(const double& AngleR );
	//���ø߶�zֵ
	inline void Set_z(const double& z );

	// �õ����еľ������ֵ
	inline double Get_Radius(void) const ;
	// �õ����еĽǶ�(����)ֵ
	inline double Get_AngleR(void) const ;
	// �õ����е�zֵ
	inline double Get_z(void) const;

private:
	double Radius_;
	double AngleR_;
	double z_;
};

#endif

