#include "GlobalDataWrap.h"
#include <BasicTool/GlobalData.h>

GlobalDataWrap::GlobalDataWrap(void)
	: db_conn_(0)
{
}


GlobalDataWrap::~GlobalDataWrap(void)
{
}


void GlobalDataWrap::Init(const QString& config_file)
{
	GlobalData::instance().SetConfigFile(config_file);
}

// 获取数据
QString GlobalDataWrap::GetConfigData(const QString& key) const
{
	return GlobalData::instance().GetConfigData(key);
}