#pragma once
#include "warheadreadwrite_global.h"
#include <QtCore>

class WarheadModelWrap;
class WARHEADREADWRITE_EXPORT WarheadRead
{
public:
	WarheadRead(void);
	~WarheadRead(void);

	//输入文件名，输出模型结构
	WarheadModelWrap* ReadXMLFile(const QString& file_name) const;
};

