//#pragma once
/********************************************************************
created:	2016/06/26
 
file base:	BIT_DAMAGESIMULATION_API
file ext:	h
author:		Xuyuxin

purpose:	Ϊ�����������ݿ��ṩ����˵��

*********************************************************************/

#ifndef BITMETALEXPLAIN_H__
#define BITMETALEXPLAIN_H__

// ��̬��
#include "Bit_MaterialDataBase_Global.h"

class BITMATERIALDATABASE_API Bit_MetalExplain
{
public:
	Bit_MetalExplain(void);
	// �������캯��
	Bit_MetalExplain( const Bit_MetalExplain& cME );
	// ���ء�=��
	Bit_MetalExplain& operator= (const Bit_MetalExplain& cME );
	// ���ء�==��
	bool operator == (const Bit_MetalExplain& cME )const;
	// ���ء�!=��
	bool operator != (const Bit_MetalExplain& cME )const;

	~Bit_MetalExplain(void);

	//���ó�ʼֵ
	void Set_Initial( const string&MMId , const string&ShoppingInformation
		, const string&HeatTreatmentExplain , const string&Remark );
	//�õ��Ƿ���
	inline bool Get_IfDefinition(void)const;
	// �õ����ϱ��
	inline string Get_MMId(void)const;
	// �õ����Ϲ�����
	inline string Get_ShoppingInformation(void)const;
	// �õ��ȴ���˵��
	inline string Get_HeatTreatmentExplain(void)const;
	// �õ���ע
	inline string Get_Remark(void)const;

private:
	//(�������Ϻţ��Բ��Ͽ�)
	string MMId_;
	//���Ϲ�����
	string ShoppingInformation_;
	//�����ȴ���˵��
	string HeatTreatmentExplain_;
	//��ע
	string Remark_;
	//�Ƿ���
	bool IfDefinition_;
};
#endif
