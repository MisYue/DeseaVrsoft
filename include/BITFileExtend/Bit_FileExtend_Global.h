/************************************************************************
	���ƣ��ļ���չ����ģ�鵼��dll��̬�������ļ�
	���ܣ�����dll
	�����ˣ���ԥ��
	����ʱ�䣺2016-6-4
	�汾��1.0
************************************************************************/

#ifndef BITFILEEXTEND_GLOBAL_H
#define BITFILEEXTEND_GLOBAL_H

//#define MATHCALCULATIONSUPPORT_EXPORTS
#ifdef BITFILEEXTEND_EXPORTS

#define BITFILEEXTEND_API __declspec(dllexport)
#else
#define BITFILEEXTEND_API __declspec(dllimport)
#endif

// ͷ�ļ�
// #include <tchar.h>
#include <fstream>
#include <string>
//#include <iostream>

using namespace std;
//template class __declspec(dllexport) std::allocator<char>;
//template class __declspec(dllexport) std::basic_string<char>;

//// ������ַ���
//#ifdef UNICODE
//typedef wchar_t BITSimChar;
//typedef std::wstring BITSimStr;
//#define BITSimStrlen wcslen  // ȡ�ÿ��ֽ��ַ������ַ����ȣ������� '/0'
//#define BITMemcpy wmemcpy    // ���ֽڵĿ���
//#define _T(x) L##x         // ���ַ���������
//#else
//	
//#endif

#endif // MATHCALCULATIONSUPPORT_GLOBAL_H