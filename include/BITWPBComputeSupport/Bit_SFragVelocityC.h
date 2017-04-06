//#pragma once

/********************************************************************
created:	2016/12/22
 
file base:	BITWPBCOMPUTESUPPORT_API
file ext:	h
author:		Xuyuxin

purpose:	���㵥����Ƭ�ٶ�

*********************************************************************/

#ifndef BITSFRAGVELOCITYC_H__
#define BITSFRAGVELOCITYC_H__
// ��̬�⵼��
#include "Bit_WPBComputeSupport_Global.h"

// ��λ��
#include "BITUnitsSupport/Bit_UnitSystem.h"
#include "BITUnitsSupport/Bit_USTransform.h"

enum FVEqutationType
{
	FVEquation_1 ,			//��ʽһ
	FVEquation_2 				//��ʽ��
};

class BITWPBCOMPUTESUPPORT_API Bit_SFragVelocityC
{
public:
	Bit_SFragVelocityC(void);
	~Bit_SFragVelocityC(void);

	//*********��ʽ˵��*********
	string EquationExplain(const FVEqutationType & Type)
	{
		switch( Type )
		{
		case FVEquation_1:
			return "���㹫ʽ1���������յ�ЧӦѧP78�������������������ܣ�װ��ȣ�һ��ϵ��";
			break;
		case FVEquation_2:
			return "���㹫ʽ2�������ڷ��յ�����ս���Ч����ս�������P274�������������΢Ԫ����׼����룬װҩֱ����װҩ���ȣ������ܣ�΢Ԫ��װ��ȣ����ϵ��";
			break;
		default:
			exit(0);
			break;
		}
	}

	//���ò���
	void SetIniParameters( const FVEqutationType &Type, const double Parameter[] 
	, const Bit_UnitSystem ParaUs[], const double Coef[] ,const Bit_UnitSystem CoefUs )
	{
		//����ϵ��
		for ( int i = 0 ; i < 10 ; i++ )
		{
			Coef_[i] = Coef[i];
		}
		Bit_USTransform *TheBit_USTransform = new Bit_USTransform;
		//�Ƚ�ϵ��������ĵ�λ�����ò���
		switch( Type )
		{
		case FVEquation_1:
			Parameter_[0] = TheBit_USTransform->
				TransformValue( ParaUs[0] , CoefUs , Parameter[0] , Velocity );
			Parameter_[1] = Parameter[1] ;
			IfUS_ = true;
			break;
		case FVEquation_2:
			Bit_USTransform *TheBit_USTransform = new Bit_USTransform;
			Parameter_[0] = TheBit_USTransform->
				TransformValue( ParaUs[0] , CoefUs , Parameter[0] , Length );
			Parameter_[1] = TheBit_USTransform->
				TransformValue( ParaUs[1] , CoefUs , Parameter[1] , Length );
			Parameter_[2] = TheBit_USTransform->
				TransformValue( ParaUs[2] , CoefUs , Parameter[2] , Length );
			Parameter_[4] = Parameter[4] ;
			IfUS_ = true;
			break;
		}
		delete TheBit_USTransform;
		IfDefine_ = true;
	}

	//����
	void Compute( const FVEqutationType & Type ); //��ʽ

	//*********�õ���ز���***********
	// �õ������Ƿ���
	bool Get_IfDefine( void ) const;
	// �õ��Ƿ��Ѽ���
	bool Get_IfCompute( void ) const;
	// �õ���λ���Ƿ���
	bool Get_IfUS( void ) const;
	// �õ���Ƭ�ٶ�
	double Get_FV( void ) const;
	// �õ�����
	double Get_Parameter( int ii ) const;
	// �õ�ϵ��
	double Get_Coef( int ii ) const;

private:
	double Parameter_[10];		//�������
	double Coef_[10];			//ϵ��
	double FV_;					//��Ƭ�ٶ�
	Bit_UnitSystem US_;			//��Ƭ�ٶȵ�λ��
	bool IfUS_;
	bool IfDefine_;				//�Ƿ���
	bool IfCompute_;			//�Ƿ����

	///////////*******��������************************
	// ��������ܹ�ʽ1
	double FragmentVelocity_F1( void )const;
	// ��������ܹ�ʽ2
	double FragmentVelocity_F2( void )const;
};
#endif
