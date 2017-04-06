//#pragma once
/********************************************************************
created:	2016/07/01
 
file base:	BIT_DAMAGESIMULATION_API
file ext:	h
author:		Xuyuxin

purpose:	��������ϵ

*********************************************************************/

// ��̬�⵼��
#include "Bit_3DCSSupport_Global.h"
//����ϵ����
#include "Bit_3DCS.h"
#include "Bit_3DCSWithExpAndUS.h"
#include "Bit_3DCSWithExplain.h"
#include "BITPointSupport/Bit_Point3D.h"

#ifndef BITPROJECTILECS_H__
#define BITPROJECTILECS_H__

class BIT3DCSSUPPORT_API Bit_3DProjectileCS
{
public:
	// �պ���
	Bit_3DProjectileCS(void);

	// �������캯��
	Bit_3DProjectileCS( const Bit_3DProjectileCS& cPCS);
	// ����"="�ź���
	Bit_3DProjectileCS& operator= (const Bit_3DProjectileCS& cPCS );
	// ����"=="��
	bool operator == (const Bit_3DProjectileCS& cPCS )const;
	// ����"!="��
	bool operator != (const Bit_3DProjectileCS& cPCS )const;
	~Bit_3DProjectileCS(void);
	//ͨ�����ý�������ϵ�ĳ�ʼ��
	inline void Set_ProjectileCS( const Bit_3DCSWithExpAndUS& RCS );
	//��λ�ƶ�ת��
	// ������λ��ת�����ǲ����
	inline void TransitionUS( const Bit_UnitSystem& NewUS );


private:
	//��������ֱ������ϵ
	Bit_3DCSWithExpAndUS RCS_;
	//�ж��Ƿ������˵�λϵͳ
	bool IfUS_;
	//��������ϵ���ڴ������ϵ�ڵ�������
	// ������(����)
	double PitchingAngle_;
	// ƫ����(����)
	double YawAngle_;
	// ��ת��(����)
	double RollAngle_;
};

#endif

