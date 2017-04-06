//#pragma once

/********************************************************************
created:	2016/02/09
 
file base:	BIT_DAMAGESIMULATION_API
file ext:	h
author:		Xuyuxin

purpose:	速度参量函数

*********************************************************************/

#include "Bit_PhysicsPBase_Global.h"

//单位制
#include "BITUnitsSupport/Bit_UnitSystem.h"

class BITPHYSICSPBASE_API Bit_Velocity 
{
public:
	Bit_Velocity(void);

	// 构造坐标系(速度大小、确定轴、速度与轴1的夹角、速度与轴2的夹角)
	Bit_Velocity( double VelocityD , Bit_UnitSystem US 
		, double Xa , double Ya , double Za );
	// 拷贝构造函数
	Bit_Velocity( const Bit_Velocity &cV );

	// 重载"="等号
	Bit_Velocity & operator = ( const Bit_Velocity & cV );
	// 重载"=="恒等判断
	bool operator == (const Bit_Velocity& cV )const;
	// 重载"!="恒等判断
	bool operator != (const Bit_Velocity& cV )const;

	~Bit_Velocity(void);

	//*****设置参数***********
	//设置初始化参数
	void Set_Initial( const double& VelocityD , const Bit_UnitSystem& US 
		, const double& Xa , const double& Ya , const double& Za );
	// 设置速度
	void Set_VelocityD( const double& VelocityD);
	// 设置单位制
	
	// 设置与X轴夹角

	// 设置与Y轴夹角

	// 设置与Z轴夹角

	// 得到速度
	inline double Get_VelocityD(void)const;
	// 得到单位制
	inline Bit_UnitSystem Get_US(void)const;
	// 得到与X轴夹角
	inline double Get_Xa(void)const;
	// 得到与Y轴夹角
	inline double Get_Ya(void)const;
	// 得到与Z轴夹角
	inline double Get_Za(void)const;

private:
	double VelocityD_;		//大小
	Bit_UnitSystem US_;
	double Xa_;				//与X轴夹角
	double Ya_;				//与y轴夹角
	double Za_;				//与z轴夹角
};

