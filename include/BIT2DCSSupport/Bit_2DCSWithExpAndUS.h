#pragma once
/********************************************************************
created:	2016/10/30
 
file base:	BIT_DAMAGESIMULATION_API
file ext:	h
author:		Xuyuxin

purpose:	2ά����ϵ����λ��˵��

*********************************************************************/

#include "Bit_2DCSSupport_Global.h"
#include "Bit_2DCSWithExplain.h"
// ����ϵ
#include "BITUnitsSupport\Bit_UnitSystem.h"

class BIT2DCSSUPPORT_API Bit_2DCSWithExpAndUS
{
public:
	//�պ���
	Bit_2DCSWithExpAndUS(void);
	//���캯��
	// ��ʼ������1
	Bit_2DCSWithExpAndUS( Bit_2DCSWithExplain TDCSExplain , Bit_UnitSystem US );
	// �������캯��
	//Bit_2DCSWithExpAndUS( const Bit_2DCSWithExpAndUS& c2DCSEaUS);
	// ����"="��
	//Bit_2DCSWithExpAndUS& operator= (const Bit_2DCSWithExpAndUS& c2DCSEaUS );
	// ����"=="��
	bool operator == (const Bit_2DCSWithExpAndUS& c2DCSEaUS )const;
	// ����"!="��
	bool operator != (const Bit_2DCSWithExpAndUS& c2DCSEaUS )const;
	//��������
	~Bit_2DCSWithExpAndUS(void);

	//���ó�ʼ����
	void Set_Initial( const Bit_2DCSWithExplain& TDCSExplain , const Bit_UnitSystem& US );
	//�õ�����ֱ������ϵ
	inline Bit_2DCSWithExplain Get_2DCSWithExplain( void ) const;
	//�õ���λ��
	Bit_UnitSystem Get_UnitSystem() const { return US_; }

private:
	//��������ֱ������ϵ
	Bit_2DCSWithExplain TDCSExplain_;
	//��λ��
	Bit_UnitSystem US_;
};

