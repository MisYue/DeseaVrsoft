/************************************************************************
	���ƣ����񻮷�ģ�鵼��dll��̬������
	���ܣ�����dll
	�����ˣ���ԥ��
	����ʱ�䣺2016-12-20
	�汾��1.1
************************************************************************/

#ifndef BITMESH_GLOBAL_H
#define BITMESH_GLOBAL_H

#ifdef BITMESH_EXPORTS

#define BITMESH_API __declspec(dllexport)
#else
#define BITMESH_API __declspec(dllimport)
#endif

// ͷ�ļ�
// #include <tchar.h>
#include <string>
using namespace std;
//template class __declspec(dllexport) std::allocator<char>;
//template class __declspec(dllexport) std::basic_string<char>;


#define pi 3.14159265358979323846			//����Piֵ = 3.1415926

#endif // BITMESHBASE_GLOBAL_H