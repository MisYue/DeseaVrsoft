#pragma once

#include "dbmdata_global.h"
#include <QtCore>

class DBMDATA_EXPORT FieldInfo
{
public:
	enum Type
	{
		kUnknown,	//δ֪����
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
	bool is_primary_key_;			//����
	bool is_foreign_key_;			//���
	bool is_allowable_null_;		//�Ƿ�����Ϊ��
	bool is_allowable_editable_;	//�Ƿ�����༭
	Type type_;						//����
	QString name_;					//����
	QString mean_;					//����
	QVariant default_;				//Ĭ��ֵ
	QString edit_limit_;			//�༭����
	QString foreign_key_table_;		//������ڱ�

};
