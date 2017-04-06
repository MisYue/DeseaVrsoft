/********************************************************************
created:	2015/03/20
 
file base:	BIT_DAMAGESIMULATION_API
file ext:	h
author:		Xuyuxin

purpose:	带说明和单位制的直角坐标系定义

*********************************************************************/

#ifndef BIT3DCSWITHEXPANDUS_H__
#define BIT3DCSWITHEXPANDUS_H__

// 动态库导出
#include "Bit_3DCSSupport_Global.h"
// 坐标系
#include "BITUnitsSupport\Bit_UnitSystem.h"
// 坐标系描述
#include "Bit_3DCSWithExplain.h"


class BIT3DCSSUPPORT_API Bit_3DCSWithExpAndUS
{
public:
	// 空
	Bit_3DCSWithExpAndUS(void);
	// 初始化方法1
	Bit_3DCSWithExpAndUS( Bit_3DCSWithExplain RCSExplain , Bit_UnitSystem US );
	// 构造初始化方法2
	Bit_3DCSWithExpAndUS( int CSId , string Name , Bit_3DCS CS , string Explain , Bit_UnitSystem US );

	// 拷贝构造函数
	Bit_3DCSWithExpAndUS( const Bit_3DCSWithExpAndUS& cCSExplainUS);
	// 重载"="号
	Bit_3DCSWithExpAndUS& operator= (const Bit_3DCSWithExpAndUS& cCSExplainUS );
	// 重载"=="号
	bool operator == (const Bit_3DCSWithExpAndUS& cCSExplainUS )const;
	// 重载"!="号
	bool operator != (const Bit_3DCSWithExpAndUS& cCSExplainUS )const;

	~Bit_3DCSWithExpAndUS(void);

	//设置初始参数
	void Set_Initial_1( const int& CSId , const string& Name , const Bit_3DCS& CS , 
		const string& Explain , const Bit_UnitSystem& US );
	//设置单位制度
	inline void Set_US(const Bit_UnitSystem& US );
	//设置坐标系编号
	inline void Set_CSId( const int& CSId );

	//得到带描述的直角坐标系
	inline Bit_3DCSWithExplain Get_RCSExplain(void) const;
	//得到坐标系编号
	inline int Get_CSId(void) const;
	//得到坐标系名字
	inline string Get_Name(void) const;
	//得到坐标系说明
	inline string Get_Explain(void) const;
	//得到单位制
	inline Bit_UnitSystem Get_US(void) const;
	//得到长度单位
	inline double Get_LengthUnit(void) const; 
	
private:
	//带描述的直角坐标系
	Bit_3DCSWithExplain RCSExplain_;
	//坐标系
	Bit_UnitSystem US_;
};
#endif
