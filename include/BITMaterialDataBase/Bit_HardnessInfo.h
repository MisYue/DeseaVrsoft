// #pragma once
/********************************************************************
created:	2016/06/04
 
file base:	BIT_DAMAGESIMULATION_API
file ext:	h
author:		Xuyuxin

purpose:	Ӳ�����ݽṹ

*********************************************************************/

#ifndef BITHARDNESSINFO_H__
#define BITHARDNESSINFO_H__

// ��̬��
#include "Bit_MaterialDataBase_Global.h"


class BITMATERIALDATABASE_API Bit_HardnessInfo
{
public:
	// �պ���
	Bit_HardnessInfo(void);
	// ���캯����ʼ��
	Bit_HardnessInfo( int HardType , double HardValue );
	// �������캯��
	Bit_HardnessInfo( const Bit_HardnessInfo& cH );
	// ���ء�=��
	Bit_HardnessInfo& operator= (const Bit_HardnessInfo& cH );
	// ���ء�==��
	bool operator == (const Bit_HardnessInfo& cH )const;
	// ���ء�!=��
	bool operator != (const Bit_HardnessInfo& cH )const;
	// ����
	~Bit_HardnessInfo(void);
	//��ʼ������
	void Set_Initial( const int & HardType , const double & HardValue);
	//�õ�Ӳ������
	inline int Get_HardType(void)const;
	//�õ�Ӳ��ֵ
	inline double Get_HardValue(void)const;

private:
	int HardType_;
	double HardValue_;
};

#endif