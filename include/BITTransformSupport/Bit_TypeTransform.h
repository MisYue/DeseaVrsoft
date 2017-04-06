/********************************************************************
created:	2016/07/9
 
file base:	BIT_DAMAGESIMULATION_API
file ext:	h
author:		Xuyuxin

purpose:	各类数据类型转换

*********************************************************************/

#ifndef BITTYPETRANSFORM_H__
#define BITTYPETRANSFORM_H__

// 动态库导出
#include "Bit_TransformSupport_Global.h"

class BITRANSFORMSUPPORT_API Bit_TypeTransform
{
public:
	Bit_TypeTransform(void);
	~Bit_TypeTransform(void);

	// String转换成double型
	double StringToDouble( const string& str)const;
	// String转换成int型
	inline int StringToInt( const string& str)const;
	
};
#endif
