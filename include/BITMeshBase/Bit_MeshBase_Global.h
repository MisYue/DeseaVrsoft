/************************************************************************
	���ƣ��������ģ�鵼��dll��̬�������ļ�BIT3DComputeSupport
	���ܣ�����dll
	�����ˣ���ԥ��
	����ʱ�䣺2016-11-14
	�汾��1.1
************************************************************************/

#ifndef BITMESHBASE_GLOBAL_H
#define BITMESHBASE_GLOBAL_H

#ifdef BITMESHBASE_EXPORTS

#define BITMESHBASE_API __declspec(dllexport)
#else
#define BITMESHBASE_API __declspec(dllimport)
#endif

// ͷ�ļ�
// #include <tchar.h>
#include <string>
using namespace std;
//template class __declspec(dllexport) std::allocator<char>;
//template class __declspec(dllexport) std::basic_string<char>;


#define pi 3.14159265358979323846			//����Piֵ = 3.1415926

#endif // BITMESHBASE_GLOBAL_H