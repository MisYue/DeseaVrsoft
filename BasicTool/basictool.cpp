#include "basictool.h"

BasicTool::BasicTool()
{

}

BasicTool::~BasicTool()
{

}
// 求浮点数的小数位数
int BasicTool::decimals(double d)
{
	int j=0;
	int k=0;
	double p=8;
	for(int i=0; d != p; ++i)
	{
		k = d * pow(10.0, i);
		p = k / pow(10.0, i);
		++j;
	}
	return j;
}

