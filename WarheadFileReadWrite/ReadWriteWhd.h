#pragma once
#include "readwritebase.h"
class ReadWriteWhd :
	public ReadWriteBase
{
public:
	ReadWriteWhd(void);
	virtual ~ReadWriteWhd(void);

	// д��ս����
	virtual bool Write(const WarheadDataEntityWrap* warhead_wrap, const QString& file_name);

	// ��ȡս����
	virtual WarheadDataEntity* Read(const QString& file_name);

	// ��ս����д��QString��
	virtual QString WriteString(const WarheadDataEntityWrap* warhead_wrap);

	// ��QString�ж�ȡս����
	virtual WarheadDataEntity* ReadString(const QString& text);
};

CREATEINSTANCE(ReadWriteWhd)

