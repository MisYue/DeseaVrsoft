//#pragma once
/********************************************************************
created:	2016/06/26
 
file base:	BIT_DAMAGESIMULATION_API
file ext:	h
author:		Xuyuxin

purpose:	为金属材料数据库提供数据说明

*********************************************************************/

#ifndef BITMETALEXPLAIN_H__
#define BITMETALEXPLAIN_H__

// 动态库
#include "Bit_MaterialDataBase_Global.h"

class BITMATERIALDATABASE_API Bit_MetalExplain
{
public:
	Bit_MetalExplain(void);
	// 拷贝构造函数
	Bit_MetalExplain( const Bit_MetalExplain& cME );
	// 重载“=”
	Bit_MetalExplain& operator= (const Bit_MetalExplain& cME );
	// 重载“==”
	bool operator == (const Bit_MetalExplain& cME )const;
	// 重载“!=”
	bool operator != (const Bit_MetalExplain& cME )const;

	~Bit_MetalExplain(void);

	//设置初始值
	void Set_Initial( const string&MMId , const string&ShoppingInformation
		, const string&HeatTreatmentExplain , const string&Remark );
	//得到是否定义
	inline bool Get_IfDefinition(void)const;
	// 得到材料编号
	inline string Get_MMId(void)const;
	// 得到材料购买厂商
	inline string Get_ShoppingInformation(void)const;
	// 得到热处理说明
	inline string Get_HeatTreatmentExplain(void)const;
	// 得到备注
	inline string Get_Remark(void)const;

private:
	//(金属材料号，对材料库)
	string MMId_;
	//材料购买厂商
	string ShoppingInformation_;
	//材料热处理说明
	string HeatTreatmentExplain_;
	//备注
	string Remark_;
	//是否定义
	bool IfDefinition_;
};
#endif
