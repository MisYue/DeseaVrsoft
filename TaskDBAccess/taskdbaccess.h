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
	// 查询任务是否存在
	bool IsExist(const QString& guid);
	// 获取任务名称
	QString GetName(const QString& guid);
	// 获取所有任务guid和名称
	void GetGuidAndNames(QMap<QString, QString>& guid_and_names);
	// 获取任务下的战斗部guid和名称
	void GetWarheadGuidAndNames(QMap<QString, QString>& guid_and_names);
protected:
	DBConn* db_conn_;
};

#endif // TASKDBACCESS_H
