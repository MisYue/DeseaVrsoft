//#pragma once
/********************************************************************
created:	2016/02/24
 
file base:	BIT_DAMAGESIMULATION_API
file ext:	h
author:		Xuyuxin

purpose:	Ϊװҩ���ݿ��ṩ���ݽṹ

*********************************************************************/

#ifndef BITCHARGEDATA_H__
#define BITCHARGEDATA_H__

#include "Bit_MaterialDataBase_Global.h"
//��λ�ƶ�
#include "BITUnitsSupport/Bit_UnitSystem.h"

class BITMATERIALDATABASE_API Bit_ChargeData
{
public:
	// �չ��캯��
	Bit_ChargeData(void);
	// �ṹ���ʼ��
	Bit_ChargeData( int Charge_Id , Bit_UnitSystem US , double Density
		, double ExplosionVelocity , double ExplosionHeat , double ExplosinPressure );
	
	// �������캯��
	Bit_ChargeData( const Bit_ChargeData& cCharData );
	// ���صȺ�
	Bit_ChargeData& operator= (const Bit_ChargeData& cCharData );
	// ����"=="��Ⱥ�
	bool operator == (const Bit_ChargeData& cCharData )const;
	// ����
	~Bit_ChargeData(void);

	// **********��������ת�����µĵ�λ����***********//
	// ������λ��ת�����ǲ����
	inline void TransitionUS( const Bit_UnitSystem& NewUS );
	// ����ת�����ȵ�λ
	inline void TransitionLength( const int& Length );
	// ����ת��ʱ�䵥λ
	inline void TransitionTime( const int& Time );
	// ����ת��������λ
	inline void TransitionMass( const int& Mass );
	// ת����λ�����
	//Bit_ChargeData TransitionUS_Input( const Bit_UnitSystem& NewUS );

	//*************88

	//��ʼ������
	void Set_Initial( const int& Charge_Id , const Bit_UnitSystem& US 
		, const double& Density , const double& ExplosionVelocity 
		, const double& ExplosionHeat , const double& ExplosinPressure );

	//�õ��Ƿ���
	inline bool Get_IfDefinition(void)const;
	//�õ�װҩId
	inline int Get_ChargeId(void)const;
	// �õ���λϵ
	inline Bit_UnitSystem Get_US(void)const;
	// �õ�װҩ�ܶȣ������뵥λ��һ�£�
	inline double Get_Density(void)const;
	// �õ�װҩ���٣������뵥λ��һ�£�
	inline double Get_ExplosionVelocity(void)const;
	// �õ�װҩ���ȣ������뵥λ��һ�£�
	inline double Get_ExplosionHeat(void)const;
	// �õ�װҩ��ѹ�������뵥λ��һ�£�
	inline double Get_ExplosinPressure(void)const;

	// �õ�װҩ�ܶȣ�mm-g-us��λϵ�����
	inline double Get_DensityForC(void)const;
	// �õ�װҩ���٣�mm-g-us��λϵ�����
	inline double Get_ExplosionVelocityForC(void)const;
	// �õ�װҩ���ȣ�mm-g-us��λϵ�����
	inline double Get_ExplosionHeatForC(void)const;
	// �õ�װҩ��ѹ��mm-g-us��λϵ�����
	inline double Get_ExplosinPressureForC(void)const;

	//ͨ��id�ŷ��ص�λϵ�������뵥λ��һ�£�
	Bit_UnitSystem Get_USOnId( const int& id )const;
	//ͨ��id�ŷ���װҩ�ܶȣ������뵥λ��һ�£�
	inline double Get_DensityOnId( const int& id )const;
	//ͨ��id�ŷ���װҩ���٣������뵥λ��һ�£�
	inline double Get_ExplosionVelocityOnId( const int& id )const;
	//ͨ��id�ŷ���װҩ���ȣ������뵥λ��һ�£�
	inline double Get_ExplosionHeatOnId( const int& id )const;
	//ͨ��id��װҩ��ѹ�������뵥λ��һ�£�
	inline double Get_ExplosinPressureOnId( const int& id )const;
	

private:
	// װҩ�ţ�Ψһʶ�����
	int Charge_Id_;
	// ��λϵ
	Bit_UnitSystem US_;
	// װҩ�ܶ�
	double Density_;
	// װҩ����
	double ExplosionVelocity_;
	// װҩ����
	double ExplosionHeat_;
	// װҩ��ѹ
	double ExplosinPressure_;
	// �Ƿ���
	bool IfDefinition_;
};
#endif
