#ifndef TASKDBACCESS_H
#define TASKDBACCESS_H

#include "taskdbaccess_global.h"
#include <QtCore>

class DBConn;
class TASKDBACCESS_EXPORT TaskDBAccess
{
public:
	TaskDBAccess(DBConn* db_conn);
	~TaskDBAccess();
	// ��ѯ�����Ƿ����
	bool IsExist(const QString& guid);
	// ��ȡ��������
	QString GetName(const QString& guid);
	// ��ȡ��������guid������
	void GetGuidAndNames(QMap<QString, QString>& guid_and_names);
	// ��ȡ�����µ�ս����guid������
	void GetWarheadGuidAndNames(QMap<QString, QString>& guid_and_names);
protected:
	DBConn* db_conn_;
};

#endif // TASKDBACCESS_H
