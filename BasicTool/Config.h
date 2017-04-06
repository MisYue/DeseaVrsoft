#pragma once
#include "basictool_global.h"
#include <QtCore>

class BASICTOOL_EXPORT Config
{
public:
	Config(void);
	virtual ~Config(void);
	Config(const QString& file_name);
	// 设置配置文件
	void SetConfigFile(const QString& file_name);
	// 保存配置
	bool SaveConfig(void);
	// 获取数据
	QString GetConfigData(const QString& key) const;
	// 设置数据
	void SetConfigData(const QString& key, const QString& data);
private:
	QMap<QString, QString> key_2_data_;
	QString file_name_;
protected:
	// 读取配置
	void ReadConfig(void);
private:
	// 解析行
	void ParserLine(const QByteArray& line);
};

