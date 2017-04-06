//***************************************
//	创建时间:	2015:11:2   17:59
//	文件名称: 	StringExtend.cpp
//	文件作者:	岳群磊
//	
//	功能说明:	实现字符串扩展类
//***************************************

#include <Windows.h>
#include "StringExtend.h"
#include <sstream>

std::string StringExtend::toString(double value)
{
	std::ostringstream os;
	if(os << value)
	{
		return os.str();
	}
	else
	{
		return "invalid conversion";
	}
}
std::string StringExtend::toString(float value)
{
	std::ostringstream os;
	if(os << value)
	{
		return os.str();
	}
	else
	{
		return "invalid conversion";
	}
}
std::string StringExtend::toString(int value)
{
	std::ostringstream os;
	if(os << value)
	{
		return os.str();
	}
	else
	{
		return "invalid conversion";
	}
}
std::string StringExtend::toString(unsigned value)
{
	std::ostringstream os;
	if(os << value)
	{
		return os.str();
	}
	else
	{
		return "invalid conversion";
	}
}

std::string StringExtend::toString(const std::vector<double>& value, const std::string& separator)
{
	std::ostringstream os;
	for(int i=0, n=value.size(); i<n; ++i)
	{
		os << value[i] << separator;
	}
	return os.str();
}
bool StringExtend::toStrings(const std::string& value, char sep, std::vector<std::string>& result)
{
	if(value.size()==0)
		return false;
	result.clear();
	std::string::size_type pos = 0;
	std::string::size_type pos_2 = 0;
	while(pos != std::string::npos)
	{
		pos_2 = value.find_first_of(sep, pos);
		result.push_back(value.substr(pos, pos_2-pos));
		if(pos_2 == std::string::npos)
			break;
		pos = pos_2+1;
	}
	return true;
}

double StringExtend::toDouble(const std::string& value)
{
	std::istringstream iss(value);
	double result = 0.0;
	iss >> result;
	return result;
}
float StringExtend::toFloat(const std::string& value)
{
	std::istringstream iss(value);
	float result = 0.0f;
	iss >> result;
	return result;
}
int StringExtend::toInt(const std::string& value)
{
	std::istringstream iss(value);
	int result = 0;
	iss >> result;
	return result;
}
unsigned StringExtend::toUnsigned(const std::string& value)
{
	std::istringstream iss(value);
	unsigned result = 0;
	iss >> result;
	return result;
}
void StringExtend::toDoubles(const std::string& value, std::vector<double>& doubles)
{
	std::istringstream iss(value);
	char separator;
	double d=0.0;
	while(!iss.eof())
	{
		iss >> d;
		if(iss.fail())
		{
			iss.clear();
			iss >> separator;
		}
		else
		{
			doubles.push_back(d);
		}
	}
}
std::string StringExtend::utf8ToGBK(const std::string& strUtf8)
{
	int len = MultiByteToWideChar(CP_UTF8, 0, strUtf8.c_str(), -1, NULL, 0);
	unsigned short* wszGBK = new unsigned short[len+1];
	memset(wszGBK, 0, len*2+2);
	MultiByteToWideChar(CP_UTF8, 0, strUtf8.c_str(), -1, (LPWSTR)wszGBK, len);
	len = WideCharToMultiByte(CP_ACP, 0, (LPWSTR)wszGBK, -1, NULL, 0, NULL, NULL);
	char* szGBK = new char[len+1];
	WideCharToMultiByte(CP_ACP, 0, (LPWSTR)wszGBK, -1, szGBK, len, NULL, NULL);
	std::string result(szGBK);
	delete[] szGBK;
	delete[] wszGBK;
	return result;
}

std::wstring StringExtend::toWstring(const std::string& value)
{
	std::wstring wstr(value.length(), L'');
	std::copy(value.begin(), value.end(), wstr.begin());
	return wstr;
}