//#pragma once
/************************************************************************
	名称：战斗部破片场计算引擎
	功能：导出dll
	创建人：徐豫新
	创建时间：2016-12-22
	版本：1.1
************************************************************************/

#ifndef BITFRAGFIELDCOMPUTE_H__
#define BITFRAGFIELDCOMPUTE_H__

// 动态库导出
#include "Bit_WPFCompute_Global.h"
#include "BITWPCDS/Bit_SFragLAVD.h"

enum FragType
{
	Pre,			//预制破片
	Nature			//自然破片
};
class Bit_FragFieldCompute
{
public:
	Bit_FragFieldCompute(void);
	~Bit_FragFieldCompute(void);

	//**********设置参数*************
	void SetIniParameters( const FragType &Type , const int FragmentN , 
		const double &RCWS , const double& GurenyE);

	//***********计算**************
	//计算破片速度

	//计算破片飞散角

private:
	int FragmentN_;
	Bit_SFragLAVD *FragG_;

	double RCWS_;
	double GurenyE_;
};
#endif
