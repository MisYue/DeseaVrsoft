/********************************************************************
created:	2016/03/20
 
file base:	BIT_DAMAGESIMULATION_API
file ext:	h
author:		Xuyuxin

purpose:	�ڵ�������ϵ�е�����ƽ��ռ�ֱ������ϵ(LocalPlaneSpaceRectangularCoordinates)

*********************************************************************/

// ��̬�⵼��
#include "Bit_3DCSSupport_Global.h"

#include "BITPointSupport/Bit_Point3D.h"

#include "Bit_3DCS.h"
//����ϵ����
#include "Bit_3DCSWithExpAndUS.h"
#include "Bit_3DCSWithExplain.h"

#ifndef BITLPSRCSBASEINGOBLE_H__
#define BITLPSRCSBASEINGOBLE_H__

class BIT3DCSSUPPORT_API Bit_3DLPSRCSGoble
{
public:
	//�պ���
	Bit_3DLPSRCSGoble(void);
	//�����ʼ��
	Bit_3DLPSRCSGoble( Bit_3DCSWithExpAndUS RCS );
	// �������캯��
	Bit_3DLPSRCSGoble( const Bit_3DLPSRCSGoble& cLPSRCS);
	// ����"="�ź���
	Bit_3DLPSRCSGoble& operator= (const Bit_3DLPSRCSGoble& cLPSRCS );

	~Bit_3DLPSRCSGoble(void);

	//ͨ�����ý�������ϵ�ĳ�ʼ��
	inline void Set_LPSRCSBaseInGoble( const Bit_3DCSWithExpAndUS& RCS );
	//��λ�ƶ�ת��
	// ������λ��ת�����ǲ����
	inline void TransitionUS( const Bit_UnitSystem& NewUS );

	//�õ�����λ�ƺ���������������ϵ
	inline Bit_3DCSWithExpAndUS Get_RCSExplainAndUS(void)const;
	//�õ�������ֱ������ϵ
	inline Bit_3DCSWithExplain Get_RCSExplain(void) const;
	//�õ���λ�ƶ�
	inline Bit_UnitSystem Get_RCSUS(void) const;
	//�õ����ȵ�λ
	inline double Get_RCSLengthUnit(void)const;
	//�õ��Ƿ����˵�λ
	inline bool Get_IfUS(void)const;
	//��������ľ��ȡ�γ�Ⱥ͸߶ȵõ���Ӧ�Ŀռ�����(�������곤��)
	Bit_Point3D ComputeRCSOnB_L_H( const double& B , const double& L, const double&H , const double& H_LengthUnit)const;
	//��������ľ��ȡ�γ�Ⱥ͸߶ȵõ���Ӧ�Ŀռ�����(�ڸö�������ϵ�ĵ�λ����)
	Bit_Point3D ComputeRCSOnB_L_HInUS( const double& B , const double& L, const double&H)const;

private:
	//��������ֱ������ϵ
	Bit_3DCSWithExpAndUS RCS_;
	//�ж��Ƿ������˵�λϵͳ
	bool IfUS_;
};
#endif
