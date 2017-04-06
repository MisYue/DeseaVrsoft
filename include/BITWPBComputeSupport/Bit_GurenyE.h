//#pragma once
/********************************************************************
created:	2016/11/25
 
file base:	BITWPBCOMPUTESUPPORT_API
file ext:	h
author:		Xuyuxin

purpose:	���������

*********************************************************************/
#ifndef BITGURENYE_H__
#define BITGURENYE_H__
// ��̬�⵼��
#include "Bit_WPBComputeSupport_Global.h"
// 
//#include "BITMaterialDataBase/Bit_ChargeData.h"
// ��λ��
#include "BITUnitsSupport/Bit_UnitSystem.h"
#include "BITUnitsSupport/Bit_USTransform.h"
// csv����������
//#include "BITFileExtend/Bit_CSVFile.h"

enum GEqutationType
{
	GEquation_1 ,			//��ʽһ
	GEquation_2 				//��ʽ��
};

class BITWPBCOMPUTESUPPORT_API Bit_GurenyE
{
public:
	Bit_GurenyE(void);
	~Bit_GurenyE(void);

	//*********��ʽ˵��*********
	string EquationExplain(const GEqutationType & Type)
	{
		switch( Type )
		{
		case GEquation_1:
			return "���㹫ʽ1���������յ�ЧӦѧP78����һ�����ٲ���������ϵ��";
			break;
		case GEquation_2:
			return "���㹫ʽ2����������ɡ����ԡ�Ԭ���ɡ���������ըҩ����ϵ����һ�ּ��׹��㷨������һ��ըҩװҩ�ܶȲ���������ϵ��";
			break;
		default:
			exit(0);
			break;
		}
	}
	//���ò���
	//
	void SetIniParameters( const GEqutationType &Type, const double Parameter[] 
	, const Bit_UnitSystem ParaUs[], const double Cof[] ,const Bit_UnitSystem CofUs )
	{
		//����ϵ��
		for ( int i = 0 ; i < 10 ; i++ )
		{
			Coef_[i] = Cof[i];
		}
		Bit_USTransform *TheBit_USTransform = new Bit_USTransform;
		//�Ƚ�ϵ��������ĵ�λ�����ò���
		switch( Type )
		{
		case GEquation_1:
			Parameter_[0] = TheBit_USTransform->
				TransformValue( ParaUs[0] , CofUs , Parameter[0] , Velocity );
			IfUS_ = true;
			break;
		case GEquation_2:
			Bit_USTransform *TheBit_USTransform = new Bit_USTransform;
			Parameter_[0] = TheBit_USTransform->
				TransformValue( ParaUs[0] , CofUs , Parameter[0] , Density );
			Parameter_[1] = TheBit_USTransform->
				TransformValue( ParaUs[1] , CofUs , Parameter[1] , Velocity );
			IfUS_ = true;
			break;
		}

		delete TheBit_USTransform;
		IfDefine_ = true;
	}
	//����
	void Compute( const GEqutationType & Type ); //��ʽ

	//*********�õ���ز���***********
	// �õ������Ƿ���
	bool Get_IfDefine( void ) const;
	// �õ��Ƿ��Ѽ���
	bool Get_IfCompute( void ) const;
	// �õ���λ���Ƿ���
	bool Get_IfUS( void ) const;
	// �õ�������
	double Get_GE( void ) const;
	// �õ�����
	double Get_Parameter( int ii ) const;
	// �õ�ϵ��
	double Get_Coef( int ii ) const;

private:
	double Parameter_[10];		//�������
	double Coef_[10];			//ϵ��
	double GE_;					//������
	Bit_UnitSystem US_;			//�����ܵ�λ��
	bool IfUS_;
	bool IfDefine_;				//�Ƿ���
	bool IfCompute_;			//�Ƿ����

	///////////*******��������************************
	// ��������ܹ�ʽ1
	double GurenyEnergy_F1( void )const;
	// ��������ܹ�ʽ2
	double GurenyEnergy_F2( void )const;
};
#endif
