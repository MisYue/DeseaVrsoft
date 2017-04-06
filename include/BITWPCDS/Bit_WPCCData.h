// #pragma once

/********************************************************************
created:	2016/12/22
 
file base:	BITWPBCOMPUTESUPPORT_API
file ext:	h
author:		Xuyuxin

purpose:	�����ܼ���ϵ�������ݽṹ

*********************************************************************/

// ��̬�⵼��
#include "Bit_WPCDS_Global.h"

// ��λ������
#include "BITUnitsSupport\Bit_UnitSystem.h"

#ifndef BITGURENYCCDATA_H__
#define BITGURENYCCDATA_H__

class BITWPCDS_API Bit_WPCCData
{
public:
	//�չ��캯��
	Bit_WPCCData(void);
	// ��ʼ�����캯��
	Bit_WPCCData( int Eid , Bit_UnitSystem US , int CN , double Coeff[] );
	// �������캯��
	Bit_WPCCData( const Bit_WPCCData &cGCD );
	// ���صȺ�
	Bit_WPCCData& operator= (const Bit_WPCCData& cGCD );
	// ����"=="��Ⱥ�
	bool operator == (const Bit_WPCCData& cGCD )const;
	// ����"!="��Ⱥ�
	bool operator != (const Bit_WPCCData& cGCD )const;
	// ����
	~Bit_WPCCData(void);

	//���ó�ʼ������
	void Set_Initial( const int Eid , const Bit_UnitSystem US , 
		const int CN , const double Coeff[] );
	
	//�õ���ʽ��
	inline int Get_Eid( void );
	//�õ���λ��
	inline Bit_UnitSystem Get_US( void );
	//�õ�ϵ������
	inline int Get_CN( void );
	//�õ�ϵ��
	inline double Get_Coeff( int ii );

private:
	int Eid_;				//��ʽ��
	Bit_UnitSystem US_;		//��λ��
	int CN_;				//ϵ������
	double Coeff_[10];		//ϵ��
};
#endif
