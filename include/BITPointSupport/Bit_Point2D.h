/********************************************************************
created:	2016/08/20
 
file base:	BIT_DAMAGESIMULATION_API
file ext:	h
author:		wangxiao

purpose:	2ά�����ݽṹ

*********************************************************************/
#include "Bit_PointSupport_Global.h"

#ifndef BITPOINT2D_H__
#define BITPOINT2D_H__

class BITPOINTSUPPORT_API Bit_Point2D
{
public: 
	//Ĭ�Ͽչ��캯��
	Bit_Point2D();
	//�������Ĺ��캯��
	Bit_Point2D( double xx , double yy );
	//�������캯��
	Bit_Point2D( const Bit_Point2D &cPoint );

	//���صȺ�
	Bit_Point2D & operator = ( const Bit_Point2D & cPoint );
	//���ؼӺ�
	Bit_Point2D operator + ( const Bit_Point2D & cPoint ) const;
	//���ؼ���
	Bit_Point2D operator - ( const Bit_Point2D & cPoint ) const;
	//���ؼӵ���
	Bit_Point2D & operator += ( const Bit_Point2D & cPoint );
	//���ؼ�����
	Bit_Point2D & operator -= ( const Bit_Point2D & cPoint );
	//���غ����
	bool operator == ( const Bit_Point2D & cPoint ) const;
	//���ز�����
	bool operator != ( const Bit_Point2D & cPoint ) const;

	//��������
	~Bit_Point2D();

	//���õ�������
	void Set_x( double xx );
	void Set_y( double yy );

	//��ȡ��������
	double Get_x( void ) const;
	double Get_y( void ) const;

private:
	double x_;//x����
	double y_;//y����
};
#endif