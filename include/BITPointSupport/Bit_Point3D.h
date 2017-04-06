/********************************************************************
created:	2015/11/03
 
file base:	BIT_DAMAGESIMULATION_API
file ext:	h
author:		Xuyuxin

purpose:	���궨�弰ת������

*********************************************************************/

#ifndef BITPOINT3D_H__
#define BITPOINT3D_H__

#include "Bit_PointSupport_Global.h"

// ����㺯��
//#include <iostream>
//#include <math.h>
//namespace BIT
//{
class BITPOINTSUPPORT_API Bit_Point3D
{
public:
	// ����յ�����
	Bit_Point3D(void);
	// �����ʼֵ����
	Bit_Point3D( double x, double y, double z );
	// ���쿽�����캯��
	Bit_Point3D( const Bit_Point3D& cPositon);

	// ���صȺ�
	Bit_Point3D& operator= (const Bit_Point3D& cPositon );
	// ���ؼ���
	Bit_Point3D operator- (const Bit_Point3D& cPositon )const;
	// ���ؼӺ�
	Bit_Point3D operator+ (const Bit_Point3D& cPositon )const;
	//���ؼӵ���
	Bit_Point3D & operator += ( const Bit_Point3D & cPoint );
	//���ؼ�����
	Bit_Point3D & operator -= ( const Bit_Point3D & cPoint );
	// ���أ��㣩�˺ţ�ÿ�������
	Bit_Point3D operator* (const Bit_Point3D& cPositon )const;

	// ���غ���ж�
	bool operator == (const Bit_Point3D& cPositon )const;
	// �����ж�
	bool operator != (const Bit_Point3D& cPositon )const;

	~Bit_Point3D(void);

	//����xֵ
	inline void Set_x(const double& xx );
	//����yֵ
	inline void Set_y(const double& yy );
	//����zֵ
	inline void Set_z(const double& zz );

	// �õ����е�xֵ
	inline double Get_x(void) const ;
	// �õ����е�yֵ
	inline double Get_y(void) const ;
	// �õ����е�zֵ
	inline double Get_z(void) const ;

	// �������������ľ���
	inline double Distance(const Bit_Point3D& p2) const;

private:
	double x_;
	double y_;
	double z_;
};
//}

#endif