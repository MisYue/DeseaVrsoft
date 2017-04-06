
/********************************************************************
created:	2016/10/30
 
file base:	BIT_DAMAGESIMULATION_API
file ext:	h
author:		Xuyuxin

purpose:	2维坐标系带说明

*********************************************************************/
#include "Bit_2DCSSupport_Global.h"
#include "Bit_2DCS.h"

#ifndef BIT2DCSWITHEXPLAIN_H__
#define BIT2DCSWITHEXPLAIN_H__

using namespace std;

class BIT2DCSSUPPORT_API Bit_2DCSWithExplain
{
public:
	// 空函数
	Bit_2DCSWithExplain(void);
	// 构造带说明坐标系
	Bit_2DCSWithExplain( int CSId , string Name , Bit_2DCS CS , string Explain );
	
	// 拷贝构造函数
	Bit_2DCSWithExplain( const Bit_2DCSWithExplain& c2DCSExplain);
	// 重载"="号
	Bit_2DCSWithExplain& operator= (const Bit_2DCSWithExplain& c2DCSExplain );
	// 重载"=="号
	bool operator == (const Bit_2DCSWithExplain& c2DCSExplain )const;
	// 重载"!="号
	bool operator != (const Bit_2DCSWithExplain& c2DCSExplain )const;


	~Bit_2DCSWithExplain(void);

	//设置初始参数
	void Set_Initial( const int& CSId 
		, const string& Name , const string& Explain , const Bit_2DCS& CS );

	//设置坐标系编号
	inline void Set_CSId( const int& CSId );
	//得到坐标系Id
	inline int Get_CSId(void) const;
	//得到坐标系名字
	inline string Get_Name(void) const;
	//得到坐标系
	inline Bit_2DCS Get_CS(void) const;
	//得到说明
	inline string Get_Explain(void) const;

private:
	int CSId_;
	string Name_;
	string Explain_;
	Bit_2DCS CS_;
};
#endif
