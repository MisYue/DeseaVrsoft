/********************************************************************
created:	2015/03/03
 
file base:	BIT_DAMAGESIMULATION_API
file ext:	h
author:		Xuyuxin

purpose:	带说明坐标系定义

*********************************************************************/

#ifndef BIT3DCSWITHEXPLAIN_H__
#define BIT3DCSWITHEXPLAIN_H__

// 动态库导出
#include "Bit_3DCSSupport_Global.h"
// 坐标系
#include "Bit_3DCS.h"
#include "BITPointSupport/Bit_Point3D.h"

class BIT3DCSSUPPORT_API Bit_3DCSWithExplain
{
public:
	// 空函数
	Bit_3DCSWithExplain(void);
	// 构造带说明坐标系
	Bit_3DCSWithExplain( int CSId , string Name , Bit_3DCS CS , string Explain );
	// 拷贝构造函数
	Bit_3DCSWithExplain( const Bit_3DCSWithExplain& cCSExplain);
	// 重载"="号
	Bit_3DCSWithExplain& operator= (const Bit_3DCSWithExplain& cCSExplain );
	// 重载"=="号
	bool operator == (const Bit_3DCSWithExplain& cCSExplain )const;
	// 重载"!="号
	bool operator != (const Bit_3DCSWithExplain& cCSExplain )const;

	//设置四个变量
	inline void Set_Initial( const int& CSId , const string& Name , const Bit_3DCS& CS , const string& Explain );
	//设置坐标系编号
	inline void Set_CSId( const int& CSId );
	//得到坐标系Id
	inline int Get_CSId(void) const;
	//得到坐标系名字
	inline string Get_Name(void) const;
	//得到坐标系
	inline Bit_3DCS Get_CS(void) const;
	//得到说明
	inline string Get_Explain(void) const;


	~Bit_3DCSWithExplain(void);

private:
	int CSId_;
	string Name_;
	string Explain_;
	Bit_3DCS CS_;
	
};
#endif
