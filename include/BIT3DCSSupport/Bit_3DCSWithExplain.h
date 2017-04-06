/********************************************************************
created:	2015/03/03
 
file base:	BIT_DAMAGESIMULATION_API
file ext:	h
author:		Xuyuxin

purpose:	��˵������ϵ����

*********************************************************************/

#ifndef BIT3DCSWITHEXPLAIN_H__
#define BIT3DCSWITHEXPLAIN_H__

// ��̬�⵼��
#include "Bit_3DCSSupport_Global.h"
// ����ϵ
#include "Bit_3DCS.h"
#include "BITPointSupport/Bit_Point3D.h"

class BIT3DCSSUPPORT_API Bit_3DCSWithExplain
{
public:
	// �պ���
	Bit_3DCSWithExplain(void);
	// �����˵������ϵ
	Bit_3DCSWithExplain( int CSId , string Name , Bit_3DCS CS , string Explain );
	// �������캯��
	Bit_3DCSWithExplain( const Bit_3DCSWithExplain& cCSExplain);
	// ����"="��
	Bit_3DCSWithExplain& operator= (const Bit_3DCSWithExplain& cCSExplain );
	// ����"=="��
	bool operator == (const Bit_3DCSWithExplain& cCSExplain )const;
	// ����"!="��
	bool operator != (const Bit_3DCSWithExplain& cCSExplain )const;

	//�����ĸ�����
	inline void Set_Initial( const int& CSId , const string& Name , const Bit_3DCS& CS , const string& Explain );
	//��������ϵ���
	inline void Set_CSId( const int& CSId );
	//�õ�����ϵId
	inline int Get_CSId(void) const;
	//�õ�����ϵ����
	inline string Get_Name(void) const;
	//�õ�����ϵ
	inline Bit_3DCS Get_CS(void) const;
	//�õ�˵��
	inline string Get_Explain(void) const;


	~Bit_3DCSWithExplain(void);

private:
	int CSId_;
	string Name_;
	string Explain_;
	Bit_3DCS CS_;
	
};
#endif
