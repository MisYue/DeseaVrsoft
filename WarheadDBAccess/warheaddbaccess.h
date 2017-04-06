#ifndef WARHEADDBACCESS_H
#define WARHEADDBACCESS_H

#include "warheaddbaccess_global.h"
#include <QtCore>

class DBConn;
class WarheadDataEntity;
class WARHEADDBACCESS_EXPORT WarheadDBAccess
{
public:
	WarheadDBAccess(DBConn* db_conn);
	~WarheadDBAccess();
	// 是否存在
	bool IsExist(const QString& guid);
	// 获取新建战斗部id
	int GetNewId(void);
	// 写入战斗部
	bool Write(const WarheadDataEntity* warhead);
	// 读取战斗部
	WarheadDataEntity* Read(const QString& guid);
	// 获取战斗部所有类别GUID和名称
	void GetClassGuidAndNames(QMap<QString, QString>& guid_and_names);
	// 获取战斗部二级类别GUID和名称
	void GetSubClassGuidAndNames(const QString& class_guid, QMap<QString, QString>& guid_and_names);
	// 获取战斗部二级类别名称
	QString GetSubClassName(const QString& guid);
	// 获取战斗部一级类别GUID和名称
	void GetClassGuidAndName(const QString& sub_class_guid, QString& class_guid, QString& class_name);
	// 获取战斗部二级类别Guid
	QString GetSubClassGuid(const QString& name);
protected:
	DBConn* db_conn_;
};

#endif // WARHEADDBACCESS_H
