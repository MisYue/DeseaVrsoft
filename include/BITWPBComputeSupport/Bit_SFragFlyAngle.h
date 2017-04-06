//#pragma once
/********************************************************************
created:	2016/12/9
 
file base:	BITWPBCOMPUTESUPPORT_API
file ext:	h
author:		Xuyuxin

purpose:	������Ƭ��ɢ�Ǽ���ɢ��Χ�ǣ�Բ����ս������

*********************************************************************/
#ifndef BITSFRAGFLYANGLE_H__
#define BITSFRAGFLYANGLE_H__
// ��̬�⵼��
#include "Bit_WPBComputeSupport_Global.h"
// ��λ��
#include "BITUnitsSupport\Bit_UnitSystem.h"
#include "BITUnitsSupport\Bit_USTransform.h"
// 2D����
#include "BIT2DComputeSupport\Bit_2DCompute.h"
// 2D��
#include "BITPointSupport\Bit_Point2D.h"

enum FVAEqutationType
{
	Taylor_Cy ,			//��Բ�����壩̩�չ�ʽ
	Shapiro_Cy,			//��Բ�����壩��Ƥ�޹�ʽ
	Shapiro_AS,			//��������״����Ƥ�޹�ʽ
};

class BITWPBCOMPUTESUPPORT_API Bit_SFragFlyAngle
{
public:
	Bit_SFragFlyAngle(void);

	~Bit_SFragFlyAngle(void);

	//*********���ü������*********
	//������������
	void SetIniParameters_P( const double & FV , const Bit_UnitSystem & FVU ,
		const double & EDV , const Bit_UnitSystem & EDVU ,
		const Bit_Point2D &FragP, const Bit_Point2D & ExploPoint ,const double & FNWAA )
	{
		//������Ƭ���г���
		FVelocity_ = FV;

		//�Ƚ���Ƭ������ըҩ���ٵĵ�λ������ըҩ����
		if ( FVU == EDVU )
		{
			EDVelocity_ = EDV;
			US_ = FVU;
		}
		else
		{
			Bit_USTransform *TheBit_USTransform = new Bit_USTransform;
			EDVelocity_ = TheBit_USTransform->TransformValue( EDVU , FVU , EDV , Velocity);
			delete TheBit_USTransform;
			US_ = FVU;
		}
		//������Ƭ���𱬵�����
		FragP_ = FragP;
		ExploPoint_ = ExploPoint;
		//������Ƭ��ը�������뵯��������ļн�
		Bit_2DCompute *TheBit_2DCompute = new Bit_2DCompute;
		Bit_Point2D EFVector = FragP_ - ExploPoint_;//�𱬵�-��Ƭλ����������
		FEWAA_ = TheBit_2DCompute->ComputeAnglePV_Xaxis( EFVector );
		delete TheBit_2DCompute;
		//������Ƭ�����뵯��������ļн�
		FNWAA_ = FNWAA;
		IfDefine_ = true;
	}
	//���ڽǶ�����
	void SetIniParameters_A( const double & FV , const Bit_UnitSystem & FVU ,
		const double & EDV , const Bit_UnitSystem & EDVU ,
		const double & FEWAA , const double & FNWAA )
	{
		//������Ƭ���г���
		FVelocity_ = FV;

		//�Ƚ���Ƭ������ըҩ���ٵĵ�λ������ըҩ����
		Bit_USTransform *TheBit_USTransform = new Bit_USTransform;
		EDVelocity_ = TheBit_USTransform->TransformValue( EDVU , FVU , EDV , Velocity);
		delete TheBit_USTransform;
		US_ = FVU;
		//������Ƭ��ը�������뵯��������ļн�
		FEWAA_ = FEWAA;
		//������Ƭ�����뵯��������ļн�
		FNWAA_ = FNWAA;
		IfDefine_ = true;
	}


	//*********���㵥����Ƭ��ɢ��*****************
	void ComputeSFFlyA( const FVAEqutationType & ET );

	//*********�õ���ز���***********
	// �õ������Ƿ���
	bool Get_IfDefine( void ) const;
	// �õ���Ƭ����
	double Get_FVelocity( void ) const;
	// �õ�ըҩ����
	double Get_EDVelocity( void ) const;
	// �õ���λ��
	Bit_UnitSystem Get_US( void ) const;
	// �õ���Ƭλ������
	Bit_Point2D Get_FragP( void ) const;
	// �õ��𱬵�����
	Bit_Point2D Get_ExploPoint( void ) const;
	// �õ���Ƭ��ը�������뵯��������ļн�
	double Get_FEWAA( void ) const;
	// �õ���Ƭ�����뵯��������ļн�
	double Get_FNWAA( void ) const;
	// �õ��Ƿ��Ѽ���
	bool Get_IfCompute( void ) const;
	// �õ�������Ƭ��ɢ��
	double Get_SFFA( void ) const;

private:
	double FVelocity_;			//��Ƭ����
	double EDVelocity_;			//ըҩ����
	Bit_UnitSystem US_;			//��λ��
	Bit_Point2D FragP_;			//��Ƭλ��
	Bit_Point2D ExploPoint_;	//�𱬵�����
	double FEWAA_;				//��Ƭ��ը�������뵯��������ļн�
	double FNWAA_;				//��Ƭ�����뵯��������ļн�;
	bool IfDefine_;				//�Ƿ���

	double SFFA_;				//������Ƭ��ɢ��
	bool IfCompute_;			//�Ƿ����

	//��ʽ1��̩�չ�ʽ(ֻ��Ӧ��Բ��)
	double Function_1( void )const;
	//��ʽ2��������Բ���ο������Ƥ�޹�ʽ
	double Function_2( void )const;
	//��ʽ3�����ʵ�̩�չ�ʽ
	double Function_3( void )const;
};
#endif
