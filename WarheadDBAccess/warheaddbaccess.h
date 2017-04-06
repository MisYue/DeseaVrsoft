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
	// �Ƿ����
	bool IsExist(const QString& guid);
	// ��ȡ�½�ս����id
	int GetNewId(void);
	// д��ս����
	bool Write(const WarheadDataEntity* warhead);
	// ��ȡս����
	WarheadDataEntity* Read(const QString& guid);
	// ��ȡս�����������GUID������
	void GetClassGuidAndNames(QMap<QString, QString>& guid_and_names);
	// ��ȡս�����������GUID������
	void GetSubClassGuidAndNames(const QString& class_guid, QMap<QString, QString>& guid_and_names);
	// ��ȡս���������������
	QString GetSubClassName(const QString& guid);
	// ��ȡս����һ�����GUID������
	void GetClassGuidAndName(const QString& sub_class_guid, QString& class_guid, QString& class_name);
	// ��ȡս�����������Guid
	QString GetSubClassGuid(const QString& name);
protected:
	DBConn* db_conn_;
};

#endif // WARHEADDBACCESS_H
