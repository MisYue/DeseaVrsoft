//***************************************
//	创建时间:	2017:3:15   9:20
//	文件名称: 	warheadfilereadwriteengine.h
//	文件作者:	岳群磊
//	
//	功能说明:	战斗部文件读写类定义，写入格式：(whd,pwr,svg,stl)，读取格式(whd)，参见文件格式说明文档
//***************************************

#ifndef WARHEADFILEREADWRITEENGINE_H
#define WARHEADFILEREADWRITEENGINE_H

#include "warheadfilereadwrite_global.h"
#include <QtCore>

class ReadWriteBase;
class WarheadDataEntity;
class WarheadDrawBase;

struct WARHEADFILEREADWRITE_EXPORT WarheadDataEntityWrap
{
	const WarheadDataEntity* warhead;	//战斗部
	const WarheadDrawBase* painter_2d;	//二维绘制对象
	const WarheadDrawBase* painter_3d;	//三维绘制对象
	QStringList pwr_to_out;	//需要输出的威力（任务GUID）列表

	WarheadDataEntityWrap();
};
typedef WarheadDataEntityWrap WarheadReadWriteWrap;

class WARHEADFILEREADWRITE_EXPORT WarheadFileReadWriteEngine
{
public:
	enum Format
	{
		kWhd,	//结构格式
		kPwr,	//威力格式
		kSvg,	//Svg结构
		kStl,	//Stl结构
	};
	WarheadFileReadWriteEngine();
	~WarheadFileReadWriteEngine();
	// 写入战斗部
	bool Write(const WarheadDataEntityWrap* warhead_wrap, const QString& file_name);
	// 读取战斗部
	WarheadDataEntity* Read(const QString& file_name);
	// 将战斗部写入QString
	QString WriteString(const WarheadDataEntityWrap* warhead_wrap, Format format);
	// 从QString中读取战斗部
	WarheadDataEntity* ReadString(const QString& text, Format format);
};

#endif // WARHEADFILEREADWRITEENGINE_H
