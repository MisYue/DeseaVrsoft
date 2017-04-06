#pragma once
#include "ReadWriteBase.h"
#include "warheadfilereadwriteengine.h"
#include <QtCore>


typedef ReadWriteBase* (*ReadWriteObjCreator)();
class ReadWriteObjFactor
{
public:
	static ReadWriteObjFactor& instance(void)
	{
		static ReadWriteObjFactor s_instance;
		return s_instance;
	}
	~ReadWriteObjFactor(void);
	// ������д����
	ReadWriteBase* Create(WarheadFileReadWriteEngine::Format format);
private:
	QMap<WarheadFileReadWriteEngine::Format, ReadWriteObjCreator> format_2_creator_;
	ReadWriteObjFactor(void);
};

