//#pragma once

/********************************************************************
created:	2016/08/03
 
file base:	BIT_DAMAGESIMULATION_API
file ext:	h
author:		Xuyuxin

purpose:	字符串的矩阵操作

*********************************************************************/

// 动态库导出
#include "Bit_FileExtend_Global.h"

#ifndef BITMATRIXSTRING_H__
#define BITMATRIXSTRING_H__

class BITFILEEXTEND_API Bit_MatrixString
{
public:
	//空函数
	Bit_MatrixString(void);
	// 构造制定行列列和初始值的矩阵
	Bit_MatrixString( int r , int c , string *MS );
	// 构造拷贝构造函数
	Bit_MatrixString(const Bit_MatrixString &cMaString );
	// 重载构造函数“=”
	Bit_MatrixString &operator=( const Bit_MatrixString &cMaString );

	~Bit_MatrixString(void);

private:
	// 矩阵行
	int MRow_;
	// 矩阵列
	int MColumn_;
	// 一维数组指针 
	string *MString_;
};
#endif
