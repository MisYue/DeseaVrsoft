
/********************************************************************
created:	2016/10/30
 
file base:	BIT_DAMAGESIMULATION_API
file ext:	h
author:		Xuyuxin

purpose:	2ά����ϵ��˵��

*********************************************************************/
#include "Bit_2DCSSupport_Global.h"
#include "Bit_2DCS.h"

#ifndef BIT2DCSWITHEXPLAIN_H__
#define BIT2DCSWITHEXPLAIN_H__

using namespace std;

class BIT2DCSSUPPORT_API Bit_2DCSWithExplain
{
public:
	// �պ���
	Bit_2DCSWithExplain(void);
	// �����˵������ϵ
	Bit_2DCSWithExplain( int CSId , string Name , Bit_2DCS CS , string Explain );
	
	// �������캯��
	Bit_2DCSWithExplain( const Bit_2DCSWithExplain& c2DCSExplain);
	// ����"="��
	Bit_2DCSWithExplain& operator= (const Bit_2DCSWithExplain& c2DCSExplain );
	// ����"=="��
	bool operator == (const Bit_2DCSWithExplain& c2DCSExplain )const;
	// ����"!="��
	bool operator != (const Bit_2DCSWithExplain& c2DCSExplain )const;


	~Bit_2DCSWithExplain(void);

	//���ó�ʼ����
	void Set_Initial( const int& CSId 
		, const string& Name , const string& Explain , const Bit_2DCS& CS );

	//��������ϵ���
	inline void Set_CSId( const int& CSId );
	//�õ�����ϵId
	inline int Get_CSId(void) const;
	//�õ�����ϵ����
	inline string Get_Name(void) const;
	//�õ�����ϵ
	inline Bit_2DCS Get_CS(void) const;
	//�õ�˵��
	inline string Get_Explain(void) const;

private:
	int CSId_;
	string Name_;
	string Explain_;
	Bit_2DCS CS_;
};
#endif
