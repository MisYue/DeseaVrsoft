/************************************************************************
	名称：带单位制点支撑模块导出dll动态库配置文件BITPointWUSSupport
	功能：导出dll
	创建人：徐豫新
	创建时间：2016-12-26
	版本：1.1
************************************************************************/

#ifndef BITPOINTWUSSUPPORT_GLOBAL_H
#define BITPOINTWUSSUPPORT_GLOBAL_H

#ifdef BITPOINTWUSSUPPORT_EXPORTS

#define BITPOINTWUSSUPPORT_API __declspec(dllexport)
#else
#define BITPOINTWUSSUPPORT_API __declspec(dllimport)
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