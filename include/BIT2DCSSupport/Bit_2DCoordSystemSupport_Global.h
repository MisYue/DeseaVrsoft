/************************************************************************
	���ƣ�2Dģ������ϵģ�鵼��dll��̬�������ļ�
	���ܣ�����dll
	�����ˣ���ԥ��
	����ʱ�䣺2016-8-24
	�汾��1.0
************************************************************************/

#ifndef BIT2DCOORDSYSTEMSUPPORT_GLOBAL_H
#define BIT2DCOORDSYSTEMSUPPORT_GLOBAL_H

//#define MATHCALCULATIONSUPPORT_EXPORTS
#ifdef BIT2DCOORDSYSTEMSUPPORT_EXPORTS

#define BIT2DCOORDSYSTEMSUPPORT_API __declspec(dllexport)
#else
#define BIT2DCOORDSYSTEMSUPPORT_API __declspec(dllimport)
#endif

// ͷ�ļ�
#include "math.h"
#include <string>
using namespace std;
template class __declspec(dllexport) std::allocator<char>;
template class __declspec(dllexport) std::basic_string<char>;

#endif 