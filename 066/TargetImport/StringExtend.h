#pragma once
#include <string>
#include <vector>

class StringExtend
{
public:
	static std::string toString(double value);
	static std::string toString(float value);
	static std::string toString(int value);
	static std::string toString(unsigned value);
	static std::string toString(const std::vector<double>& value, const std::string& separator = " ");
	static std::string toString(wchar_t* value);
	static bool toStrings(const std::string& value, char sep, std::vector<std::string>& result);
	static double toDouble(const std::string& value);
	static float toFloat(const std::string& value);
	static int toInt(const std::string& value);
	static unsigned toUnsigned(const std::string& value);
	static void toDoubles(const std::string& value, std::vector<double>& doubles);
	static std::string utf8ToGBK(const std::string& strUtf8);
	static std::wstring toWstring(const std::string& value);
};