/********************************************************************
created:	2015/03/20
 
file base:	BIT_DAMAGESIMULATION_API
file ext:	h
author:		Xuyuxin

purpose:	��˵���͵�λ�Ƶ�ֱ������ϵ����

*********************************************************************/

#ifndef BIT3DCSWITHEXPANDUS_H__
#define BIT3DCSWITHEXPANDUS_H__

// ��̬�⵼��
#include "Bit_3DCSSupport_Global.h"
// ����ϵ
#include "BITUnitsSupport\Bit_UnitSystem.h"
// ����ϵ����
#include "Bit_3DCSWithExplain.h"


class BIT3DCSSUPPORT_API Bit_3DCSWithExpAndUS
{
public:
	// ��
	Bit_3DCSWithExpAndUS(void);
	// ��ʼ������1
	Bit_3DCSWithExpAndUS( Bit_3DCSWithExplain RCSExplain , Bit_UnitSystem US );
	// �����ʼ������2
	Bit_3DCSWithExpAndUS( int CSId , string Name , Bit_3DCS CS , string Explain , Bit_UnitSystem US );

	// �������캯��
	Bit_3DCSWithExpAndUS( const Bit_3DCSWithExpAndUS& cCSExplainUS);
	// ����"="��
	Bit_3DCSWithExpAndUS& operator= (const Bit_3DCSWithExpAndUS& cCSExplainUS );
	// ����"=="��
	bool operator == (const Bit_3DCSWithExpAndUS& cCSExplainUS )const;
	// ����"!="��
	bool operator != (const Bit_3DCSWithExpAndUS& cCSExplainUS )const;

	~Bit_3DCSWithExpAndUS(void);

	//���ó�ʼ����
	void Set_Initial_1( const int& CSId , const string& Name , const Bit_3DCS& CS , 
		const string& Explain , const Bit_UnitSystem& US );
	//���õ�λ�ƶ�
	inline void Set_US(const Bit_UnitSystem& US );
	//��������ϵ���
	inline void Set_CSId( const int& CSId );

	//�õ���������ֱ������ϵ
	inline Bit_3DCSWithExplain Get_RCSExplain(void) const;
	//�õ�����ϵ���
	inline int Get_CSId(void) const;
	//�õ�����ϵ����
	inline string Get_Name(void) const;
	//�õ�����ϵ˵��
	inline string Get_Explain(void) const;
	//�õ���λ��
	inline Bit_UnitSystem Get_US(void) const;
	//�õ����ȵ�λ
	inline double Get_LengthUnit(void) const; 
	
private:
	//��������ֱ������ϵ
	Bit_3DCSWithExplain RCSExplain_;
	//����ϵ
	Bit_UnitSystem US_;
};
#endif
