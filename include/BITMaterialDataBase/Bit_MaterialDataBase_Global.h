/************************************************
	���ƣ��������ݿ����ݽṹ����dll��̬�������ļ�
	���ܣ�����dll
	�����ˣ�����
	����ʱ�䣺2015-4-11
	�汾��1.0
*************************************************/

#ifndef BITMATERIALDATABASE_GLOBAL_H
#define BITMATERIALDATABASE_GLOBAL_H


#ifdef BITMATERIALDATABASE_EXPORTS

#define BITMATERIALDATABASE_API __declspec(dllexport)
#else
#define BITMATERIALDATABASE_API __declspec(dllimport)
#endif

//ͷ�ļ�
#include <string>
#include <math.h>

using namespace std;
//template class __declspec(dllexport) std::allocator<char>;
//template class __declspec(dllexport) std::basic_string<char>;

#endif //