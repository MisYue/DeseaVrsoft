#include "Reader.h"

Reader::Reader()
{

}

Reader::~Reader()
{

}

//�������ݿ������
bool Reader::inputDateBase(string filepath)
{
	fstream getcsv( filepath , ios::out|ios::_Nocreate);
	if ( !getcsv.is_open())
	{
		return false;
	}
	else
	{
		string LineWild;//��getline����ĸ���
		string WordSingle;//������word����һ����Ԫ���е����ݣ�
		vector<string> LineDemo;//ѹ��map�ĸ���
		map<int,vector<string>>::iterator aguille;
		int i = 0 , j = 0;

		while (getline(getcsv , LineWild ))//����ÿ����Ұ�С�
		{
			i++;
			for ( j = 0 ; j < LineWild.size() ; j++ )//��ÿ����Ұ�С�����ȡ����Ԫ�������
			{
				WordSingle.push_back(LineWild.at(j));//��һ����Ԫ���е�����ѹ��wordsingle
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

//��string��ת����double
double Reader::transformStringDouble(string strFigure)
{
	double Figure = 0;//����
	double Integer = 0;//��������
	double Decimal = 0;//С������
	double Length = strFigure.size();//���ֳ���

	double Index = 0;//ָ������
	double BaseNum = 0;//��������

	int i;

	//���ж��Ƿ�Ϊ��ѧ������
	int Counter = 0;
	bool SciCount;//trueΪ��ѧ������
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
	{//�ǿ�ѧ����
		//���ж��Ƿ�Ϊ����
		if ( strFigure.at(0) != '-')
		{//����
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
		{//����
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
	{//��ѧ����
		int EPos = 0;//��E�����ڵ�λ��
		//���ж��Ƿ�Ϊ����
		if ( strFigure.at(0) != '-')
		{//����
			for ( i = 0 ; i < strFigure.size() ; i++ )
			{//�ҵ���E�����ڵ�λ��
				if ( strFigure.at(i) == 'e' || strFigure.at(i) == 'E' )
				{
					EPos = i;
				}
			}
			for ( i = strFigure.size() - 1 ; i > EPos ; i-- )
			{//��ָ������
				Index += ( strFigure.at(i) - 48 ) * pow( 10.0 , ( Length - i - 1 ));
			}
			for ( i = EPos - 1 ; i >= 0 ; i-- )
			{//���������
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
		{//����
			for ( i = 0 ; i < strFigure.size() ; i++ )
			{//�ҵ���E�����ڵ�λ��
				if ( strFigure.at(i) == 'e' || strFigure.at(i) == 'E' )
				{
					EPos = i;
				}
			}
			for ( i = strFigure.size() - 1 ; i > EPos ; i-- )
			{//��ָ������
				Index += ( strFigure.at(i) - 48 ) * pow( 10.0 , ( Length - i - 1 ));
			}
			for ( i = EPos - 1 ; i >= 1 ; i-- )
			{//���������
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

//���кš��кŻ�ȡ����
string Reader::getFigure(int ii , int jj)
{
	return m_Recorder[ii].at(jj-1);
}

int Reader::getLineCount()
{
	return m_DaBaLineCount;
}
