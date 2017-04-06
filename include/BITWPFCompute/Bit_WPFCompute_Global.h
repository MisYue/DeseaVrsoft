/************************************************************************
	名称：战斗部威力场计算支撑
	功能：导出dll
	创建人：徐豫新
	创建时间：2016-12-22
	版本：1.1
************************************************************************/

#ifndef BITWPFCOMPUTE_GLOBAL_H
#define BITWPFCOMPUTE_GLOBAL_H

#ifdef BITWPFCOMPUTE_EXPORTS

#define BITWPFCOMPUTE_API __declspec(dllexport)
#else
#define BITWPFCOMPUTE_API __declspec(dllimport)
#endif

// 头文件
// #include <tchar.h>
#include <string>
using namespace std;
//template class __declspec(dllexport) std::allocator<char>;
//template class __declspec(dllexport) std::basic_string<char>;


//#define pi 3.14159265358979323846			//定义Pi值 = 3.1415926

#endif // BITMESHBASE_GLOBAL_H