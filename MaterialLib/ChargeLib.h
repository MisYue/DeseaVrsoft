#pragma once
#include "materiallib.h"
class MATERIALLIB_EXPORT ChargeLib :
	public MaterialLib
{
public:
	ChargeLib(void);
	virtual ~ChargeLib(void);
	// ��ʼ�����Ͽ�
	virtual bool Init(const QString& csv_file);
	// ��ʼ�����Ͽ�
	virtual bool Init(DBConn* db_conn);
	// ׷�Ӳ���
	virtual const Material* Append(const QString& line);
protected:

};

