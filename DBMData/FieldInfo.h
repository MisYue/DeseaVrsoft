#pragma once

#include "dbmdata_global.h"
#include <QtCore>

class DBMDATA_EXPORT FieldInfo
{
public:
	enum Type
	{
		kUnknown,	//未知类型
		kBool,
		kInt,
		kDouble,
		kString,
		kImage,
		kEnum,
		kExpandType,
	};
	FieldInfo(void);
	virtual ~FieldInfo(void);
protected:
	bool is_primary_key_;			//主键
	bool is_foreign_key_;			//外键
	bool is_allowable_null_;		//是否允许为空
	bool is_allowable_editable_;	//是否允许编辑
	Type type_;						//类型
	QString name_;					//名称
	QString mean_;					//意义
	QVariant default_;				//默认值
	QString edit_limit_;			//编辑限制
	QString foreign_key_table_;		//外键所在表

};
