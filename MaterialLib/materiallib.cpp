#include "materiallib.h"

MaterialLib::MaterialLib()
{

}

MaterialLib::~MaterialLib()
{
	qDeleteAll(guid_2_material_.values());
}


// ��ʼ�����Ͽ�
bool MaterialLib::Init(const QString& csv_file)
{
	return false;
}


// ��ʼ�����Ͽ�
bool MaterialLib::Init(DBConn* db_conn)
{
	return false;
}


// ��ȡ���в���GUID������
QMap<QString, QString> MaterialLib::GetAllGuidAndNames(void) 
{
	return guid_2_name_;
}
