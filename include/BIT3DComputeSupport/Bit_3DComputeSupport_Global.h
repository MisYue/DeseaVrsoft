/************************************************************************
	���ƣ�3D���μ���֧��ģ�鵼��dll��̬�������ļ�BIT3DComputeSupport
	���ܣ�����dll
	�����ˣ���ԥ��
	����ʱ�䣺2016-11-14
	�汾��1.1
************************************************************************/

#ifndef BIT3DCOMPUTESUPPORT_GLOBAL_H
#define BIT3DCOMPUTESUPPORT_GLOBAL_H

#ifdef BIT3DCOMPUTESUPPORT_EXPORTS

#define BIT3DCOMPUTESUPPORT_API __declspec(dllexport)
#else
#define BIT3DCOMPUTESUPPORT_API __declspec(dllimport)
#endif

// ͷ�ļ�
// #include <tchar.h>
#include <string>
using namespace std;
//template class __declspec(dllexport) std::allocator<char>;
//template class __declspec(dllexport) std::basic_string<char>;


#define pi 3.14159265358979323846			//����Piֵ = 3.1415926

#endif // MATHCALCULATIONSUPPORT_GLOBAL_H