#pragma once
#include "warheadreadwrite_global.h"
#include <QtCore>

class WarheadModelWrap;
class WARHEADREADWRITE_EXPORT WarheadRead
{
public:
	WarheadRead(void);
	~WarheadRead(void);

	//�����ļ��������ģ�ͽṹ
	WarheadModelWrap* ReadXMLFile(const QString& file_name) const;
};

