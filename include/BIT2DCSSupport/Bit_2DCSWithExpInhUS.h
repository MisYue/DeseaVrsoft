#pragma once
/********************************************************************
created:	2016/10/30
 
file base:	BIT_DAMAGESIMULATION_API
file ext:	h
author:		Xuyuxin

purpose:	2ά����ϵ(�̳�)��λ��˵��

*********************************************************************/
#include "Bit_2DCSSupport_Global.h"

#include "Bit_2DCSWithExplain.h"
#include "BITUnitsSupport\Bit_UnitSystem.h"

class BIT2DCSSUPPORT_API Bit_2DCSWithExpInhUS :public Bit_UnitSystem
{
public:
	Bit_2DCSWithExpInhUS(void);
	//
	// ��ʼ������1
	Bit_2DCSWithExpInhUS( Bit_2DCSWithExplain TDCSExplain , Bit_UnitSystem US );
	// �������캯��
	Bit_2DCSWithExpInhUS( const Bit_2DCSWithExpInhUS& c2DCSEIUS);
	// ����"="��
	Bit_2DCSWithExpInhUS& operator= (const Bit_2DCSWithExpInhUS& c2DCSEIUS );
	// ����"=="��
	bool operator == (const Bit_2DCSWithExpInhUS& c2DCSEIUS )const;
	// ����"!="��
	bool operator != (const Bit_2DCSWithExpInhUS& c2DCSEIUS )const;

	~Bit_2DCSWithExpInhUS(void);

private:
	//��������ֱ������ϵ
	Bit_2DCSWithExplain TDCSExplain_;
};

