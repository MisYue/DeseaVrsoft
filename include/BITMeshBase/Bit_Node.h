/********************************************************************
created:	2015/11/03
 
file base:	BIT_DAMAGESIMULATION_API
file ext:	h
author:		Xuyuxin

purpose:	�ڵ㶨�弰��ؼ��㺯��

*********************************************************************/
//#pragma once
#ifndef BITNODE_H__
#define BITNODE_H__

#include "Bit_MeshBase_Global.h"

//3D����
#include "BITPointSupport/Bit_Point3D.h"
//����ߵ���ѧ��
//#include "AdvancedMath.h"
//���弸�οռ���
//#include "SpaceGeometry.h"

class BITMESHBASE_API Bit_Node
{
public:
	// ����սڵ�
	Bit_Node(void);
	// �����ʼ���ڵ㣨ID+XYZ����
	Bit_Node( int id , double x , double y , double z );
	// �����ʼ���ڵ㣨ID+coordinates���꣩
	Bit_Node( int id , Bit_Point3D& Position );//
	// �������캯��
	Bit_Node( const Bit_Node &cN );

	// ���ء�=��
	Bit_Node& operator = ( const Bit_Node& cN );
	// ���ء�==��
	bool operator == ( const Bit_Node& cN )const;

	virtual ~Bit_Node(void);

	//���ó�ʼ��
	inline void set_Initial(const int& id , const double& x 
		, const double& y , const double& z);

	//���ýڵ��е�idֵ
	inline void Set_id(const int& idid );
	//����xֵ
	inline void Set_x(const double& xx );
	//����yֵ
	inline void Set_y(const double& yy );
	//����zֵ
	inline void Set_z(const double& zz );
	//���ýڵ�����
	inline void Set_NodeCoordinate( const Bit_Point3D& N_Position );
	//���ýڵ�����
	inline void Set_NodeCoord_double( const double& x , const double& y , const double& z );
	//���ýڵ�
	inline void Set_Node( const int&id , const Bit_Point3D& N_Position );

	// �õ��ڵ��е�idֵ
	inline int Get_id(void)const;
	// �õ��ڵ��е�xֵ
	inline double Get_x(void)const;
	// �õ��ڵ��е�yֵ
	inline double Get_y(void)const;
	// �õ��ڵ��е�zֵ
	inline double Get_z(void)const;
	//�õ��ڵ�����
	inline Bit_Point3D Get_NodeCoordinates(void)const;

	///////********�ڵ�Ԥ����***************
	//�ж������ڵ��Ƿ��������ͬ
	inline bool JudgeIfSamePointIn2Nodes( const Bit_Node& N1 , const Bit_Node& N2 )const;
	//�ж϶���ڵ����Ƿ����������ͬ��
	bool JudgeIfSamePointInNNodes( const int& Num , const Bit_Node N[])const;
	//�ڵ���ظ��Ļ��ϲ��ڵ㣬�γ��µĽڵ�
	void MergeIdRepetitionNodes( const int &Num_Old , const Bit_Node N_Old[] , int *Num_new , Bit_Node N_new[] )const;


	//���ýڵ���


private:
	int id_;             // �ڵ�Ŷ���
	double x_;           // �ڵ�����X
	double y_;           // �ڵ�����Y
	double z_;           // �ڵ�����Z

};
#endif

