//#pragma once
/********************************************************************
created:	2016/12/9
 
file base:	BITWPBCOMPUTESUPPORT_API
file ext:	h
author:		Xuyuxin

purpose:	������Ƭ��λ�ú��ٶ�

*********************************************************************/

#ifndef BITSFRAGLAVD_H__
#define BITSFRAGLAVD_H__
// ��̬�⵼��
#include "Bit_WPCDS_Global.h"
// 3D��
#include "BITPointSupport/Bit_Point3D.h"
// �ٶ���
#include "BITPhysicsPBase/Bit_Velocity.h"

class BITWPCDS_API Bit_SFragLAVD
{
public:
	Bit_SFragLAVD(void);
	~Bit_SFragLAVD(void);

	//��ʼ��
	void Set_Initial( const Bit_Point3D & FragmentL , const Bit_Velocity & FragmentV );

private:
	//��Ƭλ��
	Bit_Point3D FragmentL_;
	//��λ��

	//��Ƭ�ٶ�
	Bit_Velocity FragmentV_;
};
#endif
