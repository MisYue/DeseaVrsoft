//***************************************
//	创建时间:	2017:3:15   10:22
//	文件名称: 	WarheadDrawBase.h
//	文件作者:	岳群磊
//	
//	功能说明:	战斗部绘制基类定义
//***************************************

#pragma once
#include "warhead_draw_global.h"

class WarheadModel;
class WARHEADDRAW_EXPORT WarheadDrawBase
{
public:
	WarheadDrawBase(void);
	WarheadDrawBase(WarheadModel* warhead);

	virtual ~WarheadDrawBase(void);
	// 写入文件
	virtual bool Write(const QString& file_name);
	// 绘制
	virtual void Draw(void);
	// 设置战斗部
	void set_model(WarheadModel* warhead);

protected:
	// 战斗部
	WarheadModel* model_;

};

