#pragma once
#include <QtCore>

class WarheadDataEntityWrap;
class WarheadDataEntity;
class ReadWriteBase
{
public:
	ReadWriteBase(void);
	virtual ~ReadWriteBase(void) = 0;

	// д��ս����
	virtual bool Write(const WarheadDataEntityWrap* warhead_wrap, const QString& file_name)
	{
		return false;
	}

	// ��ȡս����
	virtual WarheadDataEntity* Read(const QString& file_name)
	{
		return NULL;
	}

	// ��ս����д��QString��
	virtual QString WriteString(const WarheadDataEntityWrap* warhead_wrap)
	{
		return QString();
	}

	// ��QString�ж�ȡս����
	virtual WarheadDataEntity* ReadString(const QString& text)
	{
		return NULL;
	}
};

#define CREATEINSTANCE(ClassName) \
	static ReadWriteBase* Create##ClassName() { \
		return new ClassName; \
		} \

