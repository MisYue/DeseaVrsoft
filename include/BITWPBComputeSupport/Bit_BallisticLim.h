/********************************************************************
created:	2016/11/25
 
file base:	BITWPBCOMPUTESUPPORT_API
file ext:	h
author:		Xuyuxin

purpose:	���㵯������

*********************************************************************/
#ifndef BITBALLISTICLIM_H__
#define BITBALLISTICLIM_H__
// ��̬�⵼��
#include "Bit_WPBComputeSupport_Global.h"
// ��λ��
#include "BITUnitsSupport/Bit_UnitSystem.h"
#include "BITUnitsSupport/Bit_USTransform.h"

enum BLEqutationType
{
	BLEquation_1 			//��ʽһ
};

class BITWPBCOMPUTESUPPORT_API Bit_BallisticLim
{
public:
	Bit_BallisticLim(void);
	~Bit_BallisticLim(void);

	//*********��ʽ˵��*********
	string EquationExplain(const BLEqutationType & Type)
	{
		switch( Type )
		{
		case BLEquation_1:
			return "���㹫ʽ1���������յ�ЧӦѧP127��������������ֳ���ֱ�����а��ȡ��а��ܶȡ��ֳ�������������ǣ��뷨�߼нǣ�������ϵ��";
			break;
		default:
			exit(0);
			break;
		}
	}
	//���ò���
	//
	void SetIniParameters( const BLEqutationType &Type, const double Parameter[] 
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
		case BLEquation_1:
			Parameter_[0] = TheBit_USTransform->
				TransformValue( ParaUs[0] , CofUs , Parameter[0] , Length );
			Parameter_[1] = TheBit_USTransform->
				TransformValue( ParaUs[1] , CofUs , Parameter[1] , Length );
			Parameter_[2] = TheBit_USTransform->
				TransformValue( ParaUs[2] , CofUs , Parameter[2] , Density );
			Parameter_[3] = TheBit_USTransform->
				TransformValue( ParaUs[3] , CofUs , Parameter[3] , Mass );
			Parameter_[4] = Parameter[4];
			IfUS_ = true;
			break;
		}

		delete TheBit_USTransform;
		IfDefine_ = true;
	}
	//����
	void Compute( const BLEqutationType & Type ); //��ʽ

	//*********�õ���ز���***********
	// �õ������Ƿ���
	bool Get_IfDefine( void ) const;
	// �õ��Ƿ��Ѽ���
	bool Get_IfCompute( void ) const;
	// �õ���λ���Ƿ���
	bool Get_IfUS( void ) const;
	// �õ���������
	double Get_BL( void ) const;
	// �õ�����
	double Get_Parameter( int ii ) const;
	// �õ�ϵ��
	double Get_Coef( int ii ) const;

private:
	double Parameter_[10];		//�������()
	double Coef_[10];			//ϵ��()
	double BL_;					//��������
	Bit_UnitSystem US_;			//�������޵�λ��
	bool IfUS_;
	bool IfDefine_;				//�Ƿ���
	bool IfCompute_;			//�Ƿ����

	///////////*******��������************************
	// ���㵯�����޹�ʽ1
	double BallisticLim_F1( void )const;
};
#endif

