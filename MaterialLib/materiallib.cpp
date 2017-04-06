#include "materiallib.h"

MaterialLib::MaterialLib()
{

}

MaterialLib::~MaterialLib()
{
	qDeleteAll(guid_2_material_.values());
}


// 初始化材料库
bool MaterialLib::Init(const QString& csv_file)
{
	return false;
}


// 初始化材料库
bool MaterialLib::Init(DBConn* db_conn)
{
	return false;
}


// 获取所有材料GUID和名称
QMap<QString, QString> MaterialLib::GetAllGuidAndNames(void) 
{
	return guid_2_name_;
}
