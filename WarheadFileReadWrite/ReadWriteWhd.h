#pragma once
#include "readwritebase.h"
class ReadWriteWhd :
	public ReadWriteBase
{
public:
	ReadWriteWhd(void);
	virtual ~ReadWriteWhd(void);

	// 写入战斗部
	virtual bool Write(const WarheadDataEntityWrap* warhead_wrap, const QString& file_name);

	// 读取战斗部
	virtual WarheadDataEntity* Read(const QString& file_name);

	// 将战斗部写入QString中
	virtual QString WriteString(const WarheadDataEntityWrap* warhead_wrap);

	// 从QString中读取战斗部
	virtual WarheadDataEntity* ReadString(const QString& text);
};

CREATEINSTANCE(ReadWriteWhd)

