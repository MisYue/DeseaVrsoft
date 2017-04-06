//#pragma once

/********************************************************************
created:	2016/08/03
 
file base:	BIT_DAMAGESIMULATION_API
file ext:	h
author:		Xuyuxin

purpose:	�ַ����ľ������

*********************************************************************/

// ��̬�⵼��
#include "Bit_FileExtend_Global.h"

#ifndef BITMATRIXSTRING_H__
#define BITMATRIXSTRING_H__

class BITFILEEXTEND_API Bit_MatrixString
{
public:
	//�պ���
	Bit_MatrixString(void);
	// �����ƶ������кͳ�ʼֵ�ľ���
	Bit_MatrixString( int r , int c , string *MS );
	// ���쿽�����캯��
	Bit_MatrixString(const Bit_MatrixString &cMaString );
	// ���ع��캯����=��
	Bit_MatrixString &operator=( const Bit_MatrixString &cMaString );

	~Bit_MatrixString(void);

private:
	// ������
	int MRow_;
	// ������
	int MColumn_;
	// һά����ָ�� 
	string *MString_;
};
#endif
