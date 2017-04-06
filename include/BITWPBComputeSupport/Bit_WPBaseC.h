/********************************************************************
created:	2016/2/2
 
file base:	BIT_DAMAGESIMULATION_API
file ext:	h
author:		Xuyuxin

purpose:	���л�������

*********************************************************************/

#ifndef BITWPBASEC_H__
#define BITWPBASEC_H__
// ��̬�⵼��
#include "Bit_WPBComputeSupport_Global.h"
// ս������������
#include "BITWarheadData/Bit_WarheadBaseData.h"

class BITWPBCOMPUTESUPPORT_API Bit_WPBaseC
{
public:
	// �չ��캯��
	Bit_WPBaseC(void);

	~Bit_WPBaseC(void);

	//***********************��ս������װҩ���ݽṹ��������****************************
	//���أ�ս��������װҩ�����������
	double ComputeMassRatioForChargeAndShell( const double& WholeMass
		, const double& ChargesMass, const double& ShellMass)const;
	//����ս����Բ����װҩ�Ϳ���������
	inline double ComputeMassRatioForChargeAndShellInClinder( const double& ChargeMassInClinder
		, const double &ShellMassInClinder )const;
	//����ս����װ��ϵ��
	inline double ComputeFillCoefficient( const double& WarWholeMass, const double& ChargeWholeMass )const;
	//
	//***********************ս������װҩ���ݽṹ��������****************************
	// ս��������װҩ�����������
	double ComputeMassRatioForChargeAndShellOnWarD( const Bit_WarheadBaseData &WarheadD)const;
	// ����ս����Բ����װҩ�Ϳ���������
	double ComputeMassRatioForChargeAndShellInClinderOnWarD( const Bit_WarheadBaseData &WarheadD )const;
	// ����ս����װ��ϵ��
	double ComputeFillCoefficientOnWarD( const Bit_WarheadBaseData &WarheadD )const;
};

#endif