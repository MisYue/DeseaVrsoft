/************************************************************************
	名称：点支撑模块导出dll动态库配置文件BITPointSupport
	功能：导出dll
	创建人：徐豫新
	创建时间：2016-11-14
	版本：1.1
************************************************************************/

#ifndef BITPOINTSUPPORT_GLOBAL_H
#define BITPOINTSUPPORT_GLOBAL_H

#ifdef BITPOINTSUPPORT_EXPORTS

#define BITPOINTSUPPORT_API __declspec(dllexport)
#else
#define BITPOINTSUPPORT_API __declspec(dllimport)
#endif

// 头文件
// #include <tchar.h>
#include <string>
using namespace std;
//template class __declspec(dllexport) std::allocator<char>;
//template class __declspec(dllexport) std::basic_string<char>;
//#include <cstdlib>


#define pi 3.14159265358979323846			//定义Pi值 = 3.1415926

#endif // MATHCALCULATIONSUPPORT_GLOBAL_H