/********************************************************************
created:	2017/1/9
 
file base:	BITWPBCOMPUTESUPPORT_API
file ext:	h
author:		Xuyuxin

purpose:	������Ƭ�ٶ�˥��ϵ��

*********************************************************************/
#ifndef BITBALLISTICLIM_H__
#define BITBALLISTICLIM_H__
// ��̬�⵼��
#include "Bit_WPBComputeSupport_Global.h"
// ��λ��
#include "BITUnitsSupport/Bit_UnitSystem.h"
#include "BITUnitsSupport/Bit_USTransform.h"

enum FVDCEqutationType
{
	FVDCEquation_1 			//��ʽһ
};

class BITWPBCOMPUTESUPPORT_API Bit_SFragVDecCoef
{
public:
	Bit_SFragVDecCoef(void);
	~Bit_SFragVDecCoef(void);

	//*********��ʽ˵��*********
	string EquationExplain(const FVDCEqutationType & Type)
	{
		switch( Type )
		{
		case FVDCEquation_1:
			return "���㹫ʽ1���������յ�ЧӦѧP88�����ĸ���������Ƭ��������ϵ���������ܶȡ���Ƭ��״ϵ������Ƭ������һ��ϵ��";
			break;
		default:
			exit(0);
			break;
		}
	}

	//���ò���
	void SetIniParameters( const FVDCEqutationType &Type, const double Parameter[] 
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
		case FVDCEquation_1:
			Parameter_[0] = Parameter[0];
			Parameter_[1] = TheBit_USTransform->
				TransformValue( ParaUs[1] , CofUs , Parameter[1] , Density );
			Parameter_[2] = Parameter[2];
			Parameter_[3] = TheBit_USTransform->
				TransformValue( ParaUs[3] , CofUs , Parameter[3] , Mass );
			IfUS_ = true;
			break;
		}

		delete TheBit_USTransform;
		IfDefine_ = true;
	}
	//����
	void Compute( const FVDCEqutationType & Type ); //��ʽ

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
	double Parameter_[10];		//�������
	double Coef_[10];			//ϵ��
	double VDC_;					//�ٶ�˥��ϵ��
	Bit_UnitSystem US_;			//��λ��
	bool IfUS_;
	bool IfDefine_;				//�Ƿ���
	bool IfCompute_;			//�Ƿ����

	///////////*******��������************************
	// ���㵯�����޹�ʽ1
	double SFragVDecCoef_F1( void )const;
};
#endif

