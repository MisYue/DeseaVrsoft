/********************************************************************
created:	2016/07/9
 
file base:	BIT_DAMAGESIMULATION_API
file ext:	h
author:		Xuyuxin

purpose:	������������ת��

*********************************************************************/

#ifndef BITTYPETRANSFORM_H__
#define BITTYPETRANSFORM_H__

// ��̬�⵼��
#include "Bit_TransformSupport_Global.h"

class BITRANSFORMSUPPORT_API Bit_TypeTransform
{
public:
	Bit_TypeTransform(void);
	~Bit_TypeTransform(void);

	// Stringת����double��
	double StringToDouble( const string& str)const;
	// Stringת����int��
	inline int StringToInt( const string& str)const;
	
};
#endif
