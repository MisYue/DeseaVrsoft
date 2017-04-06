/************************************************************************
	名称：2D模型坐标系模块导出dll动态库配置文件
	功能：导出dll
	创建人：徐豫新
	创建时间：2016-8-24
	版本：1.0
************************************************************************/

#ifndef BIT2DCOORDSYSTEMSUPPORT_GLOBAL_H
#define BIT2DCOORDSYSTEMSUPPORT_GLOBAL_H

//#define MATHCALCULATIONSUPPORT_EXPORTS
#ifdef BIT2DCOORDSYSTEMSUPPORT_EXPORTS

#define BIT2DCOORDSYSTEMSUPPORT_API __declspec(dllexport)
#else
#define BIT2DCOORDSYSTEMSUPPORT_API __declspec(dllimport)
#endif

// 头文件
#include "math.h"
#include <string>
using namespace std;
template class __declspec(dllexport) std::allocator<char>;
template class __declspec(dllexport) std::basic_string<char>;

#endif 