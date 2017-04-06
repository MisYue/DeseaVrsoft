//#pragma once
/************************************************************************
	���ƣ�ս������Ƭ����������
	���ܣ�����dll
	�����ˣ���ԥ��
	����ʱ�䣺2016-12-22
	�汾��1.1
************************************************************************/

#ifndef BITFRAGFIELDCOMPUTE_H__
#define BITFRAGFIELDCOMPUTE_H__

// ��̬�⵼��
#include "Bit_WPFCompute_Global.h"
#include "BITWPCDS/Bit_SFragLAVD.h"

enum FragType
{
	Pre,			//Ԥ����Ƭ
	Nature			//��Ȼ��Ƭ
};
class Bit_FragFieldCompute
{
public:
	Bit_FragFieldCompute(void);
	~Bit_FragFieldCompute(void);

	//**********���ò���*************
	void SetIniParameters( const FragType &Type , const int FragmentN , 
		const double &RCWS , const double& GurenyE);

	//***********����**************
	//������Ƭ�ٶ�

	//������Ƭ��ɢ��

private:
	int FragmentN_;
	Bit_SFragLAVD *FragG_;

	double RCWS_;
	double GurenyE_;
};
#endif
