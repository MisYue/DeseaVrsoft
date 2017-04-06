/************************************************************************
	名称：网格划分模块导出dll动态库配置
	功能：导出dll
	创建人：徐豫新
	创建时间：2016-12-20
	版本：1.1
************************************************************************/

#ifndef BITMESH_GLOBAL_H
#define BITMESH_GLOBAL_H

#ifdef BITMESH_EXPORTS

#define BITMESH_API __declspec(dllexport)
#else
#define BITMESH_API __declspec(dllimport)
#endif

// 头文件
// #include <tchar.h>
#include <string>
using namespace std;
//template class __declspec(dllexport) std::allocator<char>;
//template class __declspec(dllexport) std::basic_string<char>;


#define pi 3.14159265358979323846			//定义Pi值 = 3.1415926

#endif // BITMESHBASE_GLOBAL_H