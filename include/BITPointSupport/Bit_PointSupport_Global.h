/************************************************************************
	���ƣ���֧��ģ�鵼��dll��̬�������ļ�BITPointSupport
	���ܣ�����dll
	�����ˣ���ԥ��
	����ʱ�䣺2016-11-14
	�汾��1.1
************************************************************************/

#ifndef BITPOINTSUPPORT_GLOBAL_H
#define BITPOINTSUPPORT_GLOBAL_H

#ifdef BITPOINTSUPPORT_EXPORTS

#define BITPOINTSUPPORT_API __declspec(dllexport)
#else
#define BITPOINTSUPPORT_API __declspec(dllimport)
#endif

// ͷ�ļ�
// #include <tchar.h>
#include <string>
using namespace std;
//template class __declspec(dllexport) std::allocator<char>;
//template class __declspec(dllexport) std::basic_string<char>;
//#include <cstdlib>


#define pi 3.14159265358979323846			//����Piֵ = 3.1415926

#endif // MATHCALCULATIONSUPPORT_GLOBAL_H