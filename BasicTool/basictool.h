#ifndef BASICTOOL_H
#define BASICTOOL_H

#include "basictool_global.h"

class BASICTOOL_EXPORT BasicTool
{
public:
	BasicTool();
	~BasicTool();
	// 求浮点数的小数位数
	static int decimals(double d);
private:

};

#endif // BASICTOOL_H
