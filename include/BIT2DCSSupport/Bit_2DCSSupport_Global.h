/************************************************************************
	���ƣ�2D����ϵ֧��ģ�鵼��dll��̬�������ļ�BIT2DCSSSupport
	���ܣ�����dll
	�����ˣ���ԥ��
	����ʱ�䣺2016-11-14
	�汾��1.1
************************************************************************/

#ifndef BIT2DCSSUPPORT_GLOBAL_H
#define BIT2DCSSUPPORT_GLOBAL_H

#ifdef BIT2DCSSUPPORT_EXPORTS

#define BIT2DCSSUPPORT_API __declspec(dllexport)
#else
#define BIT2DCSSUPPORT_API __declspec(dllimport)
#endif

// ͷ�ļ�
// #include <tchar.h>
#include <string>
using namespace std;
//template class __declspec(dllexport) std::allocator<char>;
//template class __declspec(dllexport) std::basic_string<char>;
//#include <math>


#define pi 3.14159265358979323846			//����Piֵ = 3.1415926

#endif // MATHCALCULATIONSUPPORT_GLOBAL_H