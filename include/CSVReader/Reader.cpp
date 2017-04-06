#include "Reader.h"

Reader::Reader()
{

}

Reader::~Reader()
{

}

//读入数据库的数据
bool Reader::inputDateBase(string filepath)
{
	fstream getcsv( filepath , ios::out|ios::_Nocreate);
	if ( !getcsv.is_open())
	{
		return false;
	}
	else
	{
		string LineWild;//用getline读入的各行
		string WordSingle;//单个“word”（一个单元格中的内容）
		vector<string> LineDemo;//压入map的各行
		map<int,vector<string>>::iterator aguille;
		int i = 0 , j = 0;

		while (getline(getcsv , LineWild ))//读入每个“野行”
		{
			i++;
			for ( j = 0 ; j < LineWild.size() ; j++ )//从每个“野行”中提取各单元格的内容
			{
				WordSingle.push_back(LineWild.at(j));//将一个单元格中的内容压入wordsingle
				if (LineWild.at(j) == ',' || j == LineWild.size() - 1)
				{
					if ( WordSingle.at( WordSingle.size()-1)==',')
					{
						WordSingle.pop_back();
						//WordSingle.push_back( ' ' );
					}
					LineDemo.push_back(WordSingle);
					WordSingle.clear();
				}
			}
			m_Recorder.insert( make_pair( i , LineDemo));
			LineDemo.clear();
			m_DaBaLineCount = i;
		}
		return true;
	}
	getcsv.close();
}

//将string类转换成double
double Reader::transformStringDouble(string strFigure)
{
	double Figure = 0;//数字
	double Integer = 0;//整数部分
	double Decimal = 0;//小数部分
	double Length = strFigure.size();//数字长度

	double Index = 0;//指数部分
	double BaseNum = 0;//底数部分

	int i;

	//先判断是否为科学计数法
	int Counter = 0;
	bool SciCount;//true为科学计数法
	for ( i = 0 ; i < strFigure.size() ; i++ )
	{
		if ( strFigure.at(i) == 'e' || strFigure.at(i) == 'E' )
		{
			Counter++;
		}
	}
	if ( Counter > 0 )
	{
		SciCount = true;
	}
	else
	{
		SciCount = false;
	}
	if ( !SciCount )
	{//非科学计数
		//再判断是否为负数
		if ( strFigure.at(0) != '-')
		{//正数
			for ( i = strFigure.size() - 1 ; i >= 0 ; i-- )
			{
				if ( strFigure.at(i) != '.' )
				{
					Integer += ( strFigure.at(i) - 48 ) * pow( 10.0 , ( Length - i - 1 ));
				}
				else 
				{
					Decimal = Integer;
					Integer = 0;
					Length = i;
				}
			}
			Figure = Integer + Decimal / pow( 10.0 , strFigure.size() - Length - 1 );
		}
		else
		{//负数
			for ( i = strFigure.size() - 1 ; i >= 1 ; i-- )
			{
				if ( strFigure.at(i) != '.' )
				{
					Integer += ( strFigure.at(i) - 48 ) * pow( 10.0 , ( Length - i - 1 ));
				}
				else 
				{
					Decimal = Integer;
					Integer = 0;
					Length = i;
				}
			}
			Figure = -(Integer + Decimal / pow( 10.0 , strFigure.size() - Length - 1 ));
		}
	}
	else
	{//科学计数
		int EPos = 0;//‘E’所在的位置
		//再判断是否为负数
		if ( strFigure.at(0) != '-')
		{//正数
			for ( i = 0 ; i < strFigure.size() ; i++ )
			{//找到‘E’所在的位置
				if ( strFigure.at(i) == 'e' || strFigure.at(i) == 'E' )
				{
					EPos = i;
				}
			}
			for ( i = strFigure.size() - 1 ; i > EPos ; i-- )
			{//求指数部分
				Index += ( strFigure.at(i) - 48 ) * pow( 10.0 , ( Length - i - 1 ));
			}
			for ( i = EPos - 1 ; i >= 0 ; i-- )
			{//求底数部分
				if ( strFigure.at(i) != '.' )
				{
					Integer += ( strFigure.at(i) - 48 ) * pow( 10.0 , ( Length - i - 1 ));
				}
				else 
				{
					Decimal = Integer;
					Integer = 0;
					Length = i;
				}
				BaseNum = Integer + Decimal / pow( 10.0 , strFigure.size() - Length - 1 );
			}
			Figure = BaseNum * pow( 10.0 , Index );
		}
		else
		{//负数
			for ( i = 0 ; i < strFigure.size() ; i++ )
			{//找到‘E’所在的位置
				if ( strFigure.at(i) == 'e' || strFigure.at(i) == 'E' )
				{
					EPos = i;
				}
			}
			for ( i = strFigure.size() - 1 ; i > EPos ; i-- )
			{//求指数部分
				Index += ( strFigure.at(i) - 48 ) * pow( 10.0 , ( Length - i - 1 ));
			}
			for ( i = EPos - 1 ; i >= 1 ; i-- )
			{//求底数部分
				if ( strFigure.at(i) != '.' )
				{
					Integer += ( strFigure.at(i) - 48 ) * pow( 10.0 , ( Length - i - 1 ));
				}
				else 
				{
					Decimal = Integer;
					Integer = 0;
					Length = i;
				}
				BaseNum = Integer + Decimal / pow( 10.0 , strFigure.size() - Length - 1 );
			}
			Figure = - BaseNum * pow( 10.0 , Index );
		}
	}
	return Figure;
}

//由行号、列号获取数据
string Reader::getFigure(int ii , int jj)
{
	return m_Recorder[ii].at(jj-1);
}

int Reader::getLineCount()
{
	return m_DaBaLineCount;
}
