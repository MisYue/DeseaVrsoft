//***************************************
//	创建时间:	2017:3:15   16:55
//	文件名称: 	PowerAnalysisBaseData.h
//	文件作者:	岳群磊
//	
//	功能说明:	威力分析基础数据类定义
//***************************************

#pragma once
#include "poweranalysis_global.h"
#include <WarheadModelData/WarheadModelWrap.h>
#include <QtCore>

//威力分析基础数据，即战斗部结构相关数据


class POWERANALYSIS_EXPORT PowerAnalysisBaseData
{
public:
	PowerAnalysisBaseData(const WarheadModelWrap* model_wrap);
	virtual ~PowerAnalysisBaseData(void);
	void set_warhead_wrap(WarheadModelWrap* warhead_wrap);
	const WarheadModelWrap* get_warhead_wrap() const { return model_wrap_; }
	//获取基础数据
	QString GetData(const QString& key) const;
protected:
	const WarheadModelWrap* model_wrap_;
	const WarheadModel* warhead_;
};

