/********************************************************************
created:	2016/08/24
 
file base:	BIT_DAMAGESIMULATION_API
file ext:	h
author:		Xuyuxin

purpose:	2ά����ϵ

*********************************************************************/

#include "Bit_2DCSSupport_Global.h"
#include "BITPointSupport/Bit_Point2D.h"
#include "BIT2DComputeSupport/Bit_2DCompute.h"

#ifndef BIT2DCS_H__
#define BIT2DCS_H__

class BIT2DCSSUPPORT_API Bit_2DCS
{
public:
	// �չ��캯��
	Bit_2DCS(void);
	// ��ʼ���캯��
	Bit_2DCS( Bit_Point2D OriginalPoint , int n, Bit_Point2D AixVector );
	// �������캯��
	Bit_2DCS( const Bit_2DCS &c2DC );
	//���صȺ�
	Bit_2DCS & operator = ( const Bit_2DCS & c2DC );
	//���غ����
	bool operator == ( const Bit_2DCS & c2DC ) const;
	//���ز�����
	bool operator != ( const Bit_2DCS & c2DC ) const;

	// ��������
	~Bit_2DCS(void);
	
	//���ó�ʼ����
	void Set_Initial( const Bit_Point2D& OriginalPoint , const int& n , const Bit_Point2D& AixVector );
	//�õ�����ԭ��
	inline Bit_Point2D Get_OriginalPoint( void ) const;
	//�õ�X������
	inline  Bit_Point2D Get_XAixVector( void ) const;
	//�õ�Y������
	inline  Bit_Point2D Get_YAixVector( void ) const;
private:
	// ����ԭ��
	Bit_Point2D OriginalPoint_;
	// X������
	Bit_Point2D X_AixVector_;
	// Y������
	Bit_Point2D Y_AixVector_;
};

#endif

