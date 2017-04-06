//#pragma once

/********************************************************************
created:	2016/02/09
 
file base:	BIT_DAMAGESIMULATION_API
file ext:	h
author:		Xuyuxin

purpose:	�ٶȲ�������

*********************************************************************/

#include "Bit_PhysicsPBase_Global.h"

//��λ��
#include "BITUnitsSupport/Bit_UnitSystem.h"

class BITPHYSICSPBASE_API Bit_Velocity 
{
public:
	Bit_Velocity(void);

	// ��������ϵ(�ٶȴ�С��ȷ���ᡢ�ٶ�����1�ļнǡ��ٶ�����2�ļн�)
	Bit_Velocity( double VelocityD , Bit_UnitSystem US 
		, double Xa , double Ya , double Za );
	// �������캯��
	Bit_Velocity( const Bit_Velocity &cV );

	// ����"="�Ⱥ�
	Bit_Velocity & operator = ( const Bit_Velocity & cV );
	// ����"=="����ж�
	bool operator == (const Bit_Velocity& cV )const;
	// ����"!="����ж�
	bool operator != (const Bit_Velocity& cV )const;

	~Bit_Velocity(void);

	//*****���ò���***********
	//���ó�ʼ������
	void Set_Initial( const double& VelocityD , const Bit_UnitSystem& US 
		, const double& Xa , const double& Ya , const double& Za );
	// �����ٶ�
	void Set_VelocityD( const double& VelocityD);
	// ���õ�λ��
	
	// ������X��н�

	// ������Y��н�

	// ������Z��н�

	// �õ��ٶ�
	inline double Get_VelocityD(void)const;
	// �õ���λ��
	inline Bit_UnitSystem Get_US(void)const;
	// �õ���X��н�
	inline double Get_Xa(void)const;
	// �õ���Y��н�
	inline double Get_Ya(void)const;
	// �õ���Z��н�
	inline double Get_Za(void)const;

private:
	double VelocityD_;		//��С
	Bit_UnitSystem US_;
	double Xa_;				//��X��н�
	double Ya_;				//��y��н�
	double Za_;				//��z��н�
};

