#pragma once
/********************************************************************
created:	2016/10/30
 
file base:	BIT_DAMAGESIMULATION_API
file ext:	h
author:		Xuyuxin

purpose:	2维坐标系(继承)单位制说明

*********************************************************************/
#include "Bit_2DCSSupport_Global.h"

#include "Bit_2DCSWithExplain.h"
#include "BITUnitsSupport\Bit_UnitSystem.h"

class BIT2DCSSUPPORT_API Bit_2DCSWithExpInhUS :public Bit_UnitSystem
{
public:
	Bit_2DCSWithExpInhUS(void);
	//
	// 初始化方法1
	Bit_2DCSWithExpInhUS( Bit_2DCSWithExplain TDCSExplain , Bit_UnitSystem US );
	// 拷贝构造函数
	Bit_2DCSWithExpInhUS( const Bit_2DCSWithExpInhUS& c2DCSEIUS);
	// 重载"="号
	Bit_2DCSWithExpInhUS& operator= (const Bit_2DCSWithExpInhUS& c2DCSEIUS );
	// 重载"=="号
	bool operator == (const Bit_2DCSWithExpInhUS& c2DCSEIUS )const;
	// 重载"!="号
	bool operator != (const Bit_2DCSWithExpInhUS& c2DCSEIUS )const;

	~Bit_2DCSWithExpInhUS(void);

private:
	//带描述的直角坐标系
	Bit_2DCSWithExplain TDCSExplain_;
};

