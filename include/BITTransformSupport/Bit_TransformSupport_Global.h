/************************************************************************
	名称：文件拓展工程模块导出dll动态库配置文件
	功能：导出dll
	创建人：徐豫新
	创建时间：2016-6-4
	版本：1.0
************************************************************************/

#ifndef BITTRANSFORMSUPPORT_GLOBAL_H
#define BITTRANSFORMSUPPORT_GLOBAL_H

//#define MATHCALCULATIONSUPPORT_EXPORTS
#ifdef BITTRANSFORMSUPPORT_EXPORTS

#define BITRANSFORMSUPPORT_API __declspec(dllexport)
#else
#define BITRANSFORMSUPPORT_API __declspec(dllimport)
#endif

// 头文件
// #include <tchar.h>
#include <string>
//#include <iostream>

using namespace std;
//template class __declspec(dllexport) std::allocator<char>;
//template class __declspec(dllexport) std::basic_string<char>;

//// 定义宽字符等
//#ifdef UNICODE
//typedef wchar_t BITSimChar;
//typedef std::wstring BITSimStr;
//#define BITSimStrlen wcslen  // 取得宽字节字符串中字符长度，不包含 '/0'
//#define BITMemcpy wmemcpy    // 宽字节的拷贝
//#define _T(x) L##x         // 把字符串连起来
//#else
//	
//#endif

#endif // 