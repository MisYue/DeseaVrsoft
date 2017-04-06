// #pragma once

/********************************************************************
created:	2016/12/22
 
file base:	BITWPBCOMPUTESUPPORT_API
file ext:	h
author:		Xuyuxin

purpose:	格尼能计算系数的数据结构

*********************************************************************/

// 动态库导出
#include "Bit_WPCDS_Global.h"

// 单位制数据
#include "BITUnitsSupport\Bit_UnitSystem.h"

#ifndef BITGURENYCCDATA_H__
#define BITGURENYCCDATA_H__

class BITWPCDS_API Bit_WPCCData
{
public:
	//空构造函数
	Bit_WPCCData(void);
	// 初始化构造函数
	Bit_WPCCData( int Eid , Bit_UnitSystem US , int CN , double Coeff[] );
	// 拷贝构造函数
	Bit_WPCCData( const Bit_WPCCData &cGCD );
	// 重载等号
	Bit_WPCCData& operator= (const Bit_WPCCData& cGCD );
	// 重载"=="恒等号
	bool operator == (const Bit_WPCCData& cGCD )const;
	// 重载"!="恒等号
	bool operator != (const Bit_WPCCData& cGCD )const;
	// 析构
	~Bit_WPCCData(void);

	//设置初始化参数
	void Set_Initial( const int Eid , const Bit_UnitSystem US , 
		const int CN , const double Coeff[] );
	
	//得到公式号
	inline int Get_Eid( void );
	//得到单位制
	inline Bit_UnitSystem Get_US( void );
	//得到系数个数
	inline int Get_CN( void );
	//得到系数
	inline double Get_Coeff( int ii );

private:
	int Eid_;				//公式号
	Bit_UnitSystem US_;		//单位制
	int CN_;				//系数个数
	double Coeff_[10];		//系数
};
#endif
