/********************************************************************
created:	2016/10/07
 
file base:	BIT_DAMAGESIMULATION_API
file ext:	h
author:		Xuyuxin

purpose:	3ά������(������Ŀ���Чģ��)

*********************************************************************/
#include "Bit_3DGeometrySupport_Global.h"
#include "BITPointSupport/Bit_Point3D.h"
//#include "MathCalculationSupport/AdvancedMath.h"
#include "MathCalculationSupport/Node.h"
#include "MathCalculationSupport/Bit_Surface_Quad.h"

#ifndef BITCUBOID_H__
#define BITCUBOID_H__

class BIT3DMODELSUPPORT_API Bit_Cuboid
{
public:
	// �չ��캯��
	Bit_Cuboid(void);
	// ��ʼ�����캯��
	Bit_Cuboid( CoordinatesPosition CP , double XDLength
		, double YDLength , double ZDLength, int Num_NS , int Num_QS );
	// �������캯��
	Bit_Cuboid( const Bit_Cuboid &cCb );
	//���صȺ�
	Bit_Cuboid & operator = ( const Bit_Cuboid & cCb );
	//���غ����
	bool operator == ( const Bit_Cuboid & cCb ) const;
	//���ز�����
	bool operator != ( const Bit_Cuboid & cCb ) const;
	//��������
	~Bit_Cuboid(void);

	// ���ó�ʼ��
	void Set_Initial( const CoordinatesPosition& CP , const double& XDLength 
		, const double& YDLength , const double& ZDLength);
	// �õ����ĵ�����
	inline CoordinatesPosition Get_CentrePoint( void )const;
	// �õ�X����
	inline double Get_XDLength( void )const;
	// �õ�Y����
	inline double Get_YDLength( void )const;
	// �õ�Z����
	inline double Get_ZDLength( void )const;
	//�õ�4���ڵ�
	void Get_Node( Node N[8] )const;
	//�õ�N[0],��1���ڵ�
	inline Node Get_Node_0( void )const; 
	//�õ�N[1],��2���ڵ�
	inline Node Get_Node_1( void )const; 
	//�õ�N[2],��3���ڵ�
	inline Node Get_Node_2( void )const; 
	//�õ�N[3],��4���ڵ�
	inline Node Get_Node_3( void )const; 
	//�õ�N[4],��5���ڵ�
	inline Node Get_Node_4( void )const; 
	//�õ�N[5],��6���ڵ�
	inline Node Get_Node_5( void )const; 
	//�õ�N[6],��7���ڵ�
	inline Node Get_Node_6( void )const; 
	//�õ�N[7],��8���ڵ�
	inline Node Get_Node_7( void )const;

	//�õ�6����
	void Get_SQ( Bit_Surface_Quad SQ[6] )const;

	//�õ�SQ[0]����1����
	inline Bit_Surface_Quad Get_SQ_1( void )const;
	//�õ�SQ[1]����2����
	inline Bit_Surface_Quad Get_SQ_2( void )const;
	//�õ�SQ[2]����3����
	inline Bit_Surface_Quad Get_SQ_3( void )const;
	//�õ�SQ[3]����4����
	inline Bit_Surface_Quad Get_SQ_4( void )const;
	//�õ�SQ[4]����5����
	inline Bit_Surface_Quad Get_SQ_5( void )const;
	//�õ�SQ[5]����6����
	inline Bit_Surface_Quad Get_SQ_6( void )const;

private:
	// ���ĵ�����
	CoordinatesPosition CP_;
	// X����
	double XDLength_;
	// Y����
	double YDLength_;
	// Z����
	double ZDLength_;
	// �˸��ڵ������
	Node N_[8];
	// �����ɽ������񻮷ֵ��浥Ԫ
	Bit_Surface_Quad SQ_[6];

};
#endif
