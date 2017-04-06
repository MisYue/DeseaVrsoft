#pragma once
#include <QtCore>

class WarheadDataEntityWrap;
class WarheadDataEntity;
class ReadWriteBase
{
public:
	ReadWriteBase(void);
	virtual ~ReadWriteBase(void) = 0;

	// 写入战斗部
	virtual bool Write(const WarheadDataEntityWrap* warhead_wrap, const QString& file_name)
	{
		return false;
	}

	// 读取战斗部
	virtual WarheadDataEntity* Read(const QString& file_name)
	{
		return NULL;
	}

	// 将战斗部写入QString中
	virtual QString WriteString(const WarheadDataEntityWrap* warhead_wrap)
	{
		return QString();
	}

	// 从QString中读取战斗部
	virtual WarheadDataEntity* ReadString(const QString& text)
	{
		return NULL;
	}
};

#define CREATEINSTANCE(ClassName) \
	static ReadWriteBase* Create##ClassName() { \
		return new ClassName; \
		} \

