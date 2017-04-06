// #pragma once
/********************************************************************
created:	2016/06/04
 
file base:	BIT_DAMAGESIMULATION_API
file ext:	h
author:		Xuyuxin

purpose:	硬度数据结构

*********************************************************************/

#ifndef BITHARDNESSINFO_H__
#define BITHARDNESSINFO_H__

// 动态库
#include "Bit_MaterialDataBase_Global.h"


class BITMATERIALDATABASE_API Bit_HardnessInfo
{
public:
	// 空函数
	Bit_HardnessInfo(void);
	// 构造函数初始化
	Bit_HardnessInfo( int HardType , double HardValue );
	// 拷贝构造函数
	Bit_HardnessInfo( const Bit_HardnessInfo& cH );
	// 重载“=”
	Bit_HardnessInfo& operator= (const Bit_HardnessInfo& cH );
	// 重载“==”
	bool operator == (const Bit_HardnessInfo& cH )const;
	// 重载“!=”
	bool operator != (const Bit_HardnessInfo& cH )const;
	// 析构
	~Bit_HardnessInfo(void);
	//初始化设置
	void Set_Initial( const int & HardType , const double & HardValue);
	//得到硬度类型
	inline int Get_HardType(void)const;
	//得到硬度值
	inline double Get_HardValue(void)const;

private:
	int HardType_;
	double HardValue_;
};

#endif