#include "ReadWriteObjFactor.h"
#include "ReadWriteWhd.h"
#include "warheadfilereadwriteengine.h"


ReadWriteObjFactor::ReadWriteObjFactor(void)
{
	format_2_creator_.insert(WarheadFileReadWriteEngine::kWhd, &CreateReadWriteWhd);
}


ReadWriteObjFactor::~ReadWriteObjFactor(void)
{
}

// 创建读写对象
ReadWriteBase* ReadWriteObjFactor::Create(WarheadFileReadWriteEngine::Format format)
{
	ReadWriteObjCreator creator = format_2_creator_.value(format, 0);
	if(creator)
		return creator();
	return NULL;
}
