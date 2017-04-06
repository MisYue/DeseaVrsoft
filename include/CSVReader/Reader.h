/*
名称：目标分布计算
功能：计算各目标在一定区域内均匀分布的位置
创建人：王潇
创建时间：2016-5-3
版本：1.0
*/
#pragma once

#include "CSVReader_Global.h"

#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <vector>

using namespace std;

class CSVREADER_API Reader
{
public:
	Reader();
	~Reader();

	bool inputDateBase( string filepath );//读入数据库的数据
	string getFigure( int ii , int jj );//由行号、列号获取数据,ii、jj就是行号列号，不是从0开始，无需减一
	double transformStringDouble( string strFigure );//将string类转换成double

	int getLineCount();

private:
	double m_DaBaLineCount;//数据库行数

	map< int , vector< string >> m_Recorder;//
};