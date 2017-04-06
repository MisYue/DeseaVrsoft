/********************************************************************
created:	2015/11/03
 
file base:	BIT_DAMAGESIMULATION_API
file ext:	h
author:		Xuyuxin

purpose:	节点定义及相关计算函数

*********************************************************************/
//#pragma once
#ifndef BITNODE_H__
#define BITNODE_H__

#include "Bit_MeshBase_Global.h"

//3D点类
#include "BITPointSupport/Bit_Point3D.h"
//定义高等数学类
//#include "AdvancedMath.h"
//定义几何空间类
//#include "SpaceGeometry.h"

class BITMESHBASE_API Bit_Node
{
public:
	// 构造空节点
	Bit_Node(void);
	// 构造初始化节点（ID+XYZ坐标
	Bit_Node( int id , double x , double y , double z );
	// 构造初始化节点（ID+coordinates坐标）
	Bit_Node( int id , Bit_Point3D& Position );//
	// 拷贝构造函数
	Bit_Node( const Bit_Node &cN );

	// 重载“=”
	Bit_Node& operator = ( const Bit_Node& cN );
	// 重载“==”
	bool operator == ( const Bit_Node& cN )const;

	virtual ~Bit_Node(void);

	//设置初始化
	inline void set_Initial(const int& id , const double& x 
		, const double& y , const double& z);

	//设置节点中的id值
	inline void Set_id(const int& idid );
	//设置x值
	inline void Set_x(const double& xx );
	//设置y值
	inline void Set_y(const double& yy );
	//设置z值
	inline void Set_z(const double& zz );
	//设置节点坐标
	inline void Set_NodeCoordinate( const Bit_Point3D& N_Position );
	//设置节点坐标
	inline void Set_NodeCoord_double( const double& x , const double& y , const double& z );
	//设置节点
	inline void Set_Node( const int&id , const Bit_Point3D& N_Position );

	// 得到节点中的id值
	inline int Get_id(void)const;
	// 得到节点中的x值
	inline double Get_x(void)const;
	// 得到节点中的y值
	inline double Get_y(void)const;
	// 得到节点中的z值
	inline double Get_z(void)const;
	//得到节点坐标
	inline Bit_Point3D Get_NodeCoordinates(void)const;

	///////********节点预处理***************
	//判断两个节点是否坐标点相同
	inline bool JudgeIfSamePointIn2Nodes( const Bit_Node& N1 , const Bit_Node& N2 )const;
	//判断多个节点中是否有坐标点相同的
	bool JudgeIfSamePointInNNodes( const int& Num , const Bit_Node N[])const;
	//节点号重复的话合并节点，形成新的节点
	void MergeIdRepetitionNodes( const int &Num_Old , const Bit_Node N_Old[] , int *Num_new , Bit_Node N_new[] )const;


	//设置节点组


private:
	int id_;             // 节点号定义
	double x_;           // 节点坐标X
	double y_;           // 节点坐标Y
	double z_;           // 节点坐标Z

};
#endif

