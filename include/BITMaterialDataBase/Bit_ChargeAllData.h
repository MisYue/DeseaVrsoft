/********************************************************************
created:	2016/07/8
 
file base:	BIT_DAMAGESIMULATION_API
file ext:	h
author:		Xuyuxin

purpose:	装药的所有数据，为装药数据库提供数据结构

*********************************************************************/

#ifndef BITCHARGEALLDATA_H__
#define BITCHARGEALLDATA_H__

#include "Bit_MaterialDataBase_Global.h"
//计算所用装药数据
#include "Bit_ChargeData.h"

class BITMATERIALDATABASE_API Bit_ChargeAllData
{
public:
	//空构造函数
	Bit_ChargeAllData(void);
	// 初始化构造函数
	Bit_ChargeAllData(Bit_UnitSystem US , Bit_ChargeData CD 
		, string Name , string Explain);
	// 拷贝构造函数
	Bit_ChargeAllData( const Bit_ChargeAllData& cCAD );
	// 重载等号
	Bit_ChargeAllData& operator= (const Bit_ChargeAllData& cCAD );
	// 重载"=="恒等号
	bool operator == (const Bit_ChargeAllData& cCAD )const;
	// 重载"!="恒等号
	bool operator != (const Bit_ChargeAllData& cCAD )const;
	// 析构
	~Bit_ChargeAllData(void);
	
	//*****设置参数***********
	//设置初始化参数
	void Set_Initial( const Bit_UnitSystem US , const Bit_ChargeData *CD 
		, const string Name , const string Explain );
	//仅设置装药数据
	void Set_ChargeData( const Bit_UnitSystem US , const Bit_ChargeData *CD );
	// 转换单位
	// **********所有数据转换到新的单位制中***********//
	// 三个单位均转换但是不输出
	inline void TransitionUS( const Bit_UnitSystem& NewUS );
	//得到单位制定义
	inline bool Get_IfUS(void)const;
	//得到单位制
	inline Bit_UnitSystem Get_US(void)const;
	//得到用于计算的装药数据
	inline Bit_ChargeData *Get_CD(void)const;
	// 得到装药名称
	inline string Get_Name(void)const;
	// 得到装药备注
	inline string Get_Explain(void)const;

private:
	// 单位制
	Bit_UnitSystem US_;
	// 装药数据
	Bit_ChargeData *CD_;
	// 装药名字
	string Name_;
	// 备注
	string Explain_;
	// 单位制是否定义
	bool IfUS_;
};
#endif
