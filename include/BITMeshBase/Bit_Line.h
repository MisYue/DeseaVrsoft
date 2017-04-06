/********************************************************************
created:	2015/11/03
 
file base:	BIT_DAMAGESIMULATION_API
file ext:	h
author:		Wangxiao Xuyuxin

purpose:	�߶��弰��ؼ��㺯��

*********************************************************************/
//#include "CoordinatesPosition.h"
#ifndef BITLINE_H__
#define BITLINE_H__

#include "Bit_Node.h"
#include "BITPointSupport/Bit_Point3D.h"
#include "BIT3DComputeSupport/Bit_3DCompute.h"

class BITMESHBASE_API Bit_Line
{
public:
	//������߶�
	Bit_Line(void);
	// �����ĳһ�ڵ�����(1���ڵ��1��������-(��)
	Bit_Line( int id , Bit_Point3D DirectionVector ,Bit_Node N );
	// �����ĳһλ�õ�����(1��������һ��������-(��)
	Bit_Line(int id , Bit_Point3D DirectionVector ,Bit_Point3D Point );
	// �����ʼ��ֱ�ߣ�ID+��������㣨��㡢�յ㣩��
	Bit_Line(int id , Bit_Point3D Point[2] );
	//�����ʼ��ֱ�ߣ�ID+�����ڵ㣩
	Bit_Line( int id , Bit_Node N1 , Bit_Node N2 );

	//�������캯��
	Bit_Line( const Bit_Line &cL );

	// ���ء�=��
	Bit_Line &operator=( const Bit_Line &cL );
	// ���ء�==��
	bool operator==( const Bit_Line &cL )const;

	~Bit_Line(void);

	//�����ߵ�idֵ
	inline void Set_id(const int &id );
	

	// �õ��ߵ�IDֵ
	inline int Get_id( void ) const;
	// �õ��ߵķ�������
	inline Bit_Point3D Get_Vector( void ) const;
	//�õ������������ڵ�Ľڵ���
	inline int Get_NodeNumber( void )const;
	//�õ����������Ľڵ�
	inline void Get_Node( int * NodeNumber , Bit_Node N[] )const;
	//�õ����������ĵ�һ���ڵ�
	inline Bit_Node Get_FristNode( void )const;
	//�õ����������ĵڶ����ڵ�
	inline Bit_Node Get_SecondNode( void )const;
	//ͨ��id�ŷ��ص�һ���ڵ�
	inline Bit_Node Get_FristNodeOnId( const int& id )const;
	//ͨ��id�ŷ��صڶ����ڵ�
	inline Bit_Node Get_SecondNodeOnId( const int& id )const;

	//�������ϵ�һ���ڵ㵽�ڶ����ڵ�ľ��루ֻ���������ڵ㣩
	inline double LengthOfLineS()const;
	//�������߶����ľ�����������
	inline Bit_Point3D PointFromFristNodeOnDis( const double &dis )const; 
	
	// �жϵ��Ƿ�������
	bool JudgePointIfInLine( const Bit_Point3D& P )const;

private:
	//�����
	int id_;
	//�ߵķ�������
	Bit_Point3D Vec_;
	//�������Ľڵ������������һ����
	int Node_Num_;
	//���������Ľڵ�
	Bit_Node *NodeInLine_;
};

#endif

