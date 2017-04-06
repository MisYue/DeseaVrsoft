//#pragma once
/********************************************************************
created:	2016/12/9
 
file base:	BITWPBCOMPUTESUPPORT_API
file ext:	h
author:		Xuyuxin

purpose:	单个破片的位置和速度

*********************************************************************/

#ifndef BITSFRAGLAVD_H__
#define BITSFRAGLAVD_H__
// 动态库导出
#include "Bit_WPCDS_Global.h"
// 3D点
#include "BITPointSupport/Bit_Point3D.h"
// 速度类
#include "BITPhysicsPBase/Bit_Velocity.h"

class BITWPCDS_API Bit_SFragLAVD
{
public:
	Bit_SFragLAVD(void);
	~Bit_SFragLAVD(void);

	//初始化
	void Set_Initial( const Bit_Point3D & FragmentL , const Bit_Velocity & FragmentV );

private:
	//破片位置
	Bit_Point3D FragmentL_;
	//单位制

	//破片速度
	Bit_Velocity FragmentV_;
};
#endif
