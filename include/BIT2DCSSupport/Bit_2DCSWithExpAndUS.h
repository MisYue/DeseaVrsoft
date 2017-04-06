#pragma once
/********************************************************************
created:	2016/10/30
 
file base:	BIT_DAMAGESIMULATION_API
file ext:	h
author:		Xuyuxin

purpose:	2维坐标系带单位制说明

*********************************************************************/

#include "Bit_2DCSSupport_Global.h"
#include "Bit_2DCSWithExplain.h"
// 坐标系
#include "BITUnitsSupport\Bit_UnitSystem.h"

class BIT2DCSSUPPORT_API Bit_2DCSWithExpAndUS
{
public:
	//空函数
	Bit_2DCSWithExpAndUS(void);
	//构造函数
	// 初始化方法1
	Bit_2DCSWithExpAndUS( Bit_2DCSWithExplain TDCSExplain , Bit_UnitSystem US );
	// 拷贝构造函数
	//Bit_2DCSWithExpAndUS( const Bit_2DCSWithExpAndUS& c2DCSEaUS);
	// 重载"="号
	//Bit_2DCSWithExpAndUS& operator= (const Bit_2DCSWithExpAndUS& c2DCSEaUS );
	// 重载"=="号
	bool operator == (const Bit_2DCSWithExpAndUS& c2DCSEaUS )const;
	// 重载"!="号
	bool operator != (const Bit_2DCSWithExpAndUS& c2DCSEaUS )const;
	//析构函数
	~Bit_2DCSWithExpAndUS(void);

	//设置初始参数
	void Set_Initial( const Bit_2DCSWithExplain& TDCSExplain , const Bit_UnitSystem& US );
	//得到描述直角坐标系
	inline Bit_2DCSWithExplain Get_2DCSWithExplain( void ) const;
	//得到单位制
	Bit_UnitSystem Get_UnitSystem() const { return US_; }

private:
	//带描述的直角坐标系
	Bit_2DCSWithExplain TDCSExplain_;
	//单位制
	Bit_UnitSystem US_;
};

