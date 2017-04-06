/************************************************************************
	名称：2D坐标系支撑模块导出dll动态库配置文件BIT2DCSSSupport
	功能：导出dll
	创建人：徐豫新
	创建时间：2016-11-14
	版本：1.1
************************************************************************/

#ifndef BIT2DCSSUPPORT_GLOBAL_H
#define BIT2DCSSUPPORT_GLOBAL_H

#ifdef BIT2DCSSUPPORT_EXPORTS

#define BIT2DCSSUPPORT_API __declspec(dllexport)
#else
#define BIT2DCSSUPPORT_API __declspec(dllimport)
#endif

// 头文件
// #include <tchar.h>
#include <string>
using namespace std;
//template class __declspec(dllexport) std::allocator<char>;
//template class __declspec(dllexport) std::basic_string<char>;
//#include <math>


#define pi 3.14159265358979323846			//定义Pi值 = 3.1415926

#endif // MATHCALCULATIONSUPPORT_GLOBAL_H