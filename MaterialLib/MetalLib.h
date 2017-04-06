#pragma once
#include "materiallib.h"

class MATERIALLIB_EXPORT MetalLib :
	public MaterialLib
{
public:
	MetalLib(void);
	virtual ~MetalLib(void);
	// 初始化材料库
	virtual bool Init(const QString& csv_file);
	// 初始化材料库
	virtual bool Init(DBConn* db_conn);
	// 追加材料
	virtual const Material* Append(const QString& line);
protected:

};

