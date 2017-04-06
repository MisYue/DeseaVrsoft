/********************************************************************
created:	2016/07/8
 
file base:	BIT_DAMAGESIMULATION_API
file ext:	h
author:		Xuyuxin

purpose:	װҩ���������ݣ�Ϊװҩ���ݿ��ṩ���ݽṹ

*********************************************************************/

#ifndef BITCHARGEALLDATA_H__
#define BITCHARGEALLDATA_H__

#include "Bit_MaterialDataBase_Global.h"
//��������װҩ����
#include "Bit_ChargeData.h"

class BITMATERIALDATABASE_API Bit_ChargeAllData
{
public:
	//�չ��캯��
	Bit_ChargeAllData(void);
	// ��ʼ�����캯��
	Bit_ChargeAllData(Bit_UnitSystem US , Bit_ChargeData CD 
		, string Name , string Explain);
	// �������캯��
	Bit_ChargeAllData( const Bit_ChargeAllData& cCAD );
	// ���صȺ�
	Bit_ChargeAllData& operator= (const Bit_ChargeAllData& cCAD );
	// ����"=="��Ⱥ�
	bool operator == (const Bit_ChargeAllData& cCAD )const;
	// ����"!="��Ⱥ�
	bool operator != (const Bit_ChargeAllData& cCAD )const;
	// ����
	~Bit_ChargeAllData(void);
	
	//*****���ò���***********
	//���ó�ʼ������
	void Set_Initial( const Bit_UnitSystem US , const Bit_ChargeData *CD 
		, const string Name , const string Explain );
	//������װҩ����
	void Set_ChargeData( const Bit_UnitSystem US , const Bit_ChargeData *CD );
	// ת����λ
	// **********��������ת�����µĵ�λ����***********//
	// ������λ��ת�����ǲ����
	inline void TransitionUS( const Bit_UnitSystem& NewUS );
	//�õ���λ�ƶ���
	inline bool Get_IfUS(void)const;
	//�õ���λ��
	inline Bit_UnitSystem Get_US(void)const;
	//�õ����ڼ����װҩ����
	inline Bit_ChargeData *Get_CD(void)const;
	// �õ�װҩ����
	inline string Get_Name(void)const;
	// �õ�װҩ��ע
	inline string Get_Explain(void)const;

private:
	// ��λ��
	Bit_UnitSystem US_;
	// װҩ����
	Bit_ChargeData *CD_;
	// װҩ����
	string Name_;
	// ��ע
	string Explain_;
	// ��λ���Ƿ���
	bool IfUS_;
};
#endif
